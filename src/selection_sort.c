#include "sort.h"
#include "swap.h"

void selection_sort(void * base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *)) {
  char * A = base;
  for (size_t j = 0; j < nmemb; j++) {
    char * min = &A[j * size];
    for (size_t i = j + 1; i < nmemb; i++) {
      if (compar(&A[i * size], min) < 0)
        min = &A[i * size];
    }
    if (&A[j * size] != min)
      SWAP(&A[j * size], min, size);
  }
}
