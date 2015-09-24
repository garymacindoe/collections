#ifndef SORT_H
#define SORT_H

#include <stddef.h>

void insertion_sort(void *, size_t, size_t, int (*)(const void *, const void *));
void selection_sort(void *, size_t, size_t, int (*)(const void *, const void *));
void merge_sort(void *, size_t, size_t, int (*)(const void *, const void *), void *);
void bubble_sort(void *, size_t, size_t, int (*)(const void *, const void *));
void heap_sort(void *, size_t, size_t, int (*)(const void *, const void *));

#endif
