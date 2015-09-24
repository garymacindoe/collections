#ifndef HEAPIFY_H
#define HEAPIFY_H

#include <stddef.h>
#include <stdbool.h>
#include "swap.h"

static inline void heapify(size_t i, void * base, size_t nmemb, size_t size,
                           int (*compar)(const void *, const void *)) {
  char * A = (char *)base;
  while (true) {
    const size_t left = 2 * i + 1;
    const size_t right = 2 * i + 2;
    size_t largest = i;
    if (left < nmemb && compar(A + largest * size, A + left * size) < 0)
      largest = left;
    if (right < nmemb && compar(A + largest * size, A + right * size) < 0)
      largest = right;
    if (largest != i) {
      SWAP(A + i * size, A + largest * size, size);
      i = largest;
    }
    else
      break;
  }
}

#endif
