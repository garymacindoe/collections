#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "search.h"

#define N 10

static int * haystack;

static int suite_init() {
  if ((haystack = malloc(N * sizeof(int))) == NULL)
    return 1;
  return 0;
}

static int suite_cleanup() {
  free(haystack);
  return 0;
}

static void setup_ascending() {
  for (int i = 0; i < N; i++)
    haystack[i] = i;
}

static void setup_descending() {
  for (int i = 0; i < N; i++)
    haystack[i] = N - i - 1;
}

static void setup_random() {
  haystack[0] = 1;
  haystack[1] = 5;
  haystack[2] = 2;
  haystack[3] = 8;
  haystack[4] = 4;
  haystack[5] = 9;
  haystack[6] = 7;
  haystack[7] = 6;
  haystack[8] = 3;
  haystack[9] = 0;
}

static int compare(const void * a, const void * b) {
  const int x = *((const int *)a);
  const int y = *((const int *)b);
  return (x < y) ? -1 : ((x > y) ? 1 : 0);
}

static void test_linear_search() {
  const int needle = 5;
  CU_ASSERT(*(int *)linear_search(&needle, haystack, N, sizeof(int), compare) == needle);
}

static void test_binary_search() {
  const int needle = 5;
  CU_ASSERT(*(int *)binary_search(&needle, haystack, N, sizeof(int), compare) == needle);
}

static const CU_TestInfo tests[] = {
  { "linear search", test_linear_search },
  CU_TEST_INFO_NULL
};

static const CU_TestInfo tests_sorted[] = {
  { "linear search", test_linear_search },
  { "binary search", test_binary_search },
  CU_TEST_INFO_NULL
};

const CU_SuiteInfo suites[] = {
  { "search ascending", suite_init, suite_cleanup, setup_ascending, NULL, (CU_TestInfo *)tests_sorted },
  { "search descending", suite_init, suite_cleanup, setup_descending, NULL, (CU_TestInfo *)tests },
  { "search random", suite_init, suite_cleanup, setup_random, NULL, (CU_TestInfo *)tests },
  CU_SUITE_INFO_NULL
};
