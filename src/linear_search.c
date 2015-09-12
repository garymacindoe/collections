#include "search.h"

const void * linear_search(const void * key, const void * base, size_t nmemb,
                           size_t size, int (*compar)(const void *, const void *)) {
  const char * start = (const char *)base;
  const char * end = &start[nmemb * size];
  while (start != end) {
    if (compar(key, start) == 0)
      return start;
    start += size;
  }
  return NULL;
}
