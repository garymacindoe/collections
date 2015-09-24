#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "heap.h"

#define N 15

static int * array;

static int suite_init() {
  if ((array = malloc(N * sizeof(int))) == NULL)
    return 1;
  return 0;
}

static int suite_cleanup() {
  free(array);
  return 0;
}

static void setup_ascending() {
  for (int i = 0; i < N; i++)
    array[i] = i;
}

static void setup_descending() {
  for (int i = 0; i < N; i++)
    array[i] = N - i - 1;
}

static void setup_random() {
  array[ 0] =  9;
  array[ 1] =  2;
  array[ 2] =  6;
  array[ 3] =  0;
  array[ 4] = 11;
  array[ 5] = 10;
  array[ 6] =  5;
  array[ 7] =  7;
  array[ 8] = 14;
  array[ 9] =  3;
  array[10] =  8;
  array[11] = 13;
  array[12] =  1;
  array[13] = 12;
  array[14] =  4;
}

static int compare(const void * a, const void * b) {
  const int x = *((const int *)a);
  const int y = *((const int *)b);
  return (x < y) ? -1 : ((x > y) ? 1 : 0);
}

static void test_make_heap() {
  make_heap(array, N, sizeof(int), compare);
  for (int i = 1; i < N; i++)
    CU_ASSERT(array[(i - 1) >> 1] >= array[i]);
}

static const CU_TestInfo tests[] = {
  { "make heap", test_make_heap },
  CU_TEST_INFO_NULL
};

const CU_SuiteInfo suites[] = {
  { "heap ascending", suite_init, suite_cleanup, setup_ascending, NULL, (CU_TestInfo *)tests },
  { "heap descending", suite_init, suite_cleanup, setup_descending, NULL, (CU_TestInfo *)tests },
  { "heap random", suite_init, suite_cleanup, setup_random, NULL, (CU_TestInfo *)tests },
  CU_SUITE_INFO_NULL
};
