#include "sort.h"
#include "copy.h"

void insertion_sort(void * base, size_t nmemb, size_t size,
                    int (*compar)(const void *, const void *)) {
  char * A = base;
  for (size_t j = 1; j < nmemb; j++) {
    char key[size];
    COPY(key, &A[j * size], size);
    size_t i = j;
    while (i > 0 && compar(key, &A[(i - 1) * size]) < 0) {
      COPY(&A[i * size], &A[(i - 1) * size], size);
      i--;
    }
    COPY(&A[i * size], key, size);
  }
}
