#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void make_heap(void *, size_t, size_t, int (*)(const void *, const void *));

#endif
