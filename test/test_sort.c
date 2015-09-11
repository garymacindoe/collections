#include <CUnit/CUnit.h>
#include <stdlib.h>
#include "sort.h"

#define N 10

static int * array = NULL, * temp = NULL;

static int suite_init() {
  if ((array = malloc(N * sizeof(int))) == NULL ||
      (temp = malloc(N * sizeof(int))) == NULL) {
    free(array);
    free(temp);
    return 1;
  }
  return 0;
}

static int suite_cleanup() {
  free(array);
  free(temp);
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
  array[0] = 1;
  array[1] = 5;
  array[2] = 2;
  array[3] = 8;
  array[4] = 4;
  array[5] = 9;
  array[6] = 7;
  array[7] = 6;
  array[8] = 3;
  array[9] = 0;
}

static int compare(const void * a, const void * b) {
  const int x = *((const int *)a);
  const int y = *((const int *)b);
  return (x < y) ? -1 : ((x > y) ? 1 : 0);
}

static void test_insertion_sort() {
  insertion_sort(array, N, sizeof(int), compare);
  for (int i = 1; i < N; i++)
    CU_ASSERT(array[i - 1] <= array[i]);
}

static void test_selection_sort() {
  selection_sort(array, N, sizeof(int), compare);
  for (int i = 1; i < N; i++)
    CU_ASSERT(array[i - 1] <= array[i]);
}

static void test_merge_sort() {
  merge_sort(array, N, sizeof(int), compare, temp);
  for (int i = 1; i < N; i++)
    CU_ASSERT(array[i - 1] <= array[i]);
}

static void test_bubble_sort() {
  bubble_sort(array, N, sizeof(int), compare);
  for (int i = 1; i < N; i++)
    CU_ASSERT(array[i - 1] <= array[i]);
}

static const CU_TestInfo tests[] = {
  { "insertion sort", test_insertion_sort },
  { "selection sort", test_selection_sort },
  { "merge sort", test_merge_sort },
  { "bubble sort", test_bubble_sort },
  CU_TEST_INFO_NULL
};

const CU_SuiteInfo suites[] = {
  { "sort ascending", suite_init, suite_cleanup, setup_ascending, NULL, (CU_TestInfo *)tests },
  { "sort descending", suite_init, suite_cleanup, setup_descending, NULL, (CU_TestInfo *)tests },
  { "sort random", suite_init, suite_cleanup, setup_random, NULL, (CU_TestInfo *)tests },
  CU_SUITE_INFO_NULL
};
