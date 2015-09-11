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
