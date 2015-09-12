#ifndef SWAP_H
#define SWAP_H

#include <stdbool.h>

#define SWAP(x, y, n) \
 do { \
   char * _a = (x), * _b = (y), _c; \
   size_t _i = (n);\
   while (_i-- > 0) { \
     _c = *_a; *_a++ = *_b; *_b++ = _c; \
   } \
 } while (false)

#endif
