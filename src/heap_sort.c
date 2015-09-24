#include "sort.h"
#include "swap.h"
#include "heap.h"
#include "heapify.h"

void heap_sort(void * base, size_t nmemb, size_t size,
               int (*compar)(const void *, const void *)) {
  char * A = (char *)base;
  make_heap(base, nmemb, size, compar);
  for (size_t i = nmemb - 1; i > 0; i--) {
    SWAP(A, A + i * size, size);
    heapify(0, A, i, size, compar);
  }
}
