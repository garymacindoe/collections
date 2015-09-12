#include "sort.h"
#include "swap.h"

void bubble_sort(void * base, size_t nmemb, size_t size,
                 int (*compar)(const void *, const void *)) {
  char * A = base;
  for (size_t i = 0; i < nmemb; i++) {
    for (size_t j = nmemb - 1; j > i; j--) {
      if (compar(&A[j * size], &A[(j - 1) * size]) < 0)
        SWAP(&A[j * size], &A[(j - 1) * size], size);
    }
  }
}
