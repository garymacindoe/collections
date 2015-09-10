#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

const void * linear_search(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));

#endif
