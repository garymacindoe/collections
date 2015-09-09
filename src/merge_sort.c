#include "sort.h"
#include <stdbool.h>

#define COPY(x, y, n) \
 do { \
   char * __a = (x); \
   const char * __b = (y); \
   size_t __i = (n); \
   while (__i-- > 0) \
     *__a++ = *__b++; \
 } while (false)

void merge_sort(void * base, size_t nmemb, size_t size,
                int (*compar)(const void *, const void *), void * temp) {
  if (nmemb < 2)
    return;

  const size_t m = nmemb / 2;
  const size_t n = nmemb - m;
  char * left = (char *)base;
  char * right = &left[m * size];
  merge_sort(left, m, size, compar, temp);
  merge_sort(right, n, size, compar, temp);

  char * c = (char *)temp;
  size_t i = 0, j = 0, k = 0;
  while (i < m && j < n) {
    if (compar(&left[i * size], &right[j * size]) < 0)
      COPY(&c[k++ * size], &left[i++ * size], size);
    else
      COPY(&c[k++ * size], &right[j++ * size], size);
  }
  COPY(&c[k * size], &left[i * size], (m - i) * size);
  COPY(&c[k * size], &right[j * size], (n - j) * size);
  COPY(base, temp, nmemb * size);
}
