#ifndef COPY_H
#define COPY_H

#include <stddef.h>
#include <stdbool.h>

#define COPY(x, y, n) \
 do { \
   char * _a = (x); \
   const char * _b = (y); \
   size_t __i = (n); \
   while (__i-- > 0) \
     *_a++ = *_b++; \
 } while (false)

#endif
