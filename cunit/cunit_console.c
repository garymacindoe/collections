#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <getopt.h>

#define CU_ERROR_CHECK(expr) \
  do { \
    CU_ErrorCode error; \
    if ((error = (expr)) != CUE_SUCCESS) { \
      fprintf(stderr, "Error calling " #expr " (%s:%d): %s\n", __FILE__, \
              __LINE__, CU_get_error_msg()); \
      return error; \
    } \
  } while (false)

extern CU_SuiteInfo suites[];

int main() {
  CU_ERROR_CHECK(CU_initialize_registry());

  CU_ERROR_CHECK(CU_register_suites(suites));

  CU_console_run_tests();

  unsigned int failures = CU_get_number_of_failures();

  CU_cleanup_registry();

  return (int)failures;
}
