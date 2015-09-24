#include "heap.h"
#include "heapify.h"

void make_heap(void * base, size_t nmemb, size_t size,
               int (*compar)(const void *, const void *)) {
  size_t i = nmemb / 2;
  while (i-- > 0)
    heapify(i, (char *)base, nmemb, size, compar);
}
