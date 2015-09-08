#include "sort.h"
#include <stdbool.h>

#define SWAP(x, y, n) \
 do { \
   char * __a = (x), * __b = (y), __c; \
   size_t __i = (n);\
   while (__i-- > 0) { \
     __c = *__a; *__a++ = *__b; *__b++ = __c; \
   } \
 } while (false)

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
