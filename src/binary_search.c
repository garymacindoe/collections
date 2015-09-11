#include "search.h"

const void * binary_search(const void * key, const void * base, size_t nmemb,
                           size_t size, int (*compar)(const void *, const void *)) {
  const char * A = (const char *)base;
  size_t left = 0, right = nmemb;
  while (left < right) {
    size_t mid = (right - left) / 2;
    int c = compar(key, &A[mid * size]);
    if (c < 0)
      right = mid;
    else if (c > 0)
      left = mid;
    else
      return &A[mid * size];
  }
  return NULL;
}
