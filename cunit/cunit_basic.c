#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
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

extern const CU_SuiteInfo suites[];

int main(int argc, char * argv[]) {
  bool help = false;
  const char * suite_name = NULL, * test_name = NULL;
  CU_BasicRunMode mode = CU_BRM_NORMAL;
  const struct option longopts[] = {
    { "suite",   required_argument,   NULL, 's'            },
    { "test",    required_argument,   NULL, 't'            },
    { "quiet",   no_argument, (int *)&mode, CU_BRM_SILENT  },
    { "verbose", no_argument, (int *)&mode, CU_BRM_VERBOSE },
    { "help",    no_argument, (int *)&help, (int)true      },
    { NULL,      0,                   NULL, 0              }
  };

  opterr = 0;
  int c, longindex;
  while ((c = getopt_long(argc, argv, ":s:t:qvh", longopts, &longindex)) != -1) {
    switch (c) {
      case 's':
        suite_name = optarg;
        break;
      case 't':
        test_name = optarg;
        break;
      case 'q':
        mode = CU_BRM_SILENT;
        break;
      case 'v':
        mode = CU_BRM_VERBOSE;
        break;
      case 'h':
        help = true;
        break;
      case ':':
        fprintf(stderr, "Missing argument for option '%c'\n", optopt);
        return -1;
      case '?':
        fprintf(stderr, "Unknown option '%c'\n", optopt);
        return -1;
    }
  }

  if (help) {
    printf("Usage: %s [-s|--suite=<suite> [-t|--test=<test>]] [-q|--quiet] [-v|--verbose] [-h|--help]\n", argv[0]);
    puts("Where:");
    puts("  -s|--suite    run all tests in a particular suite");
    puts("  -t|--test     run a specific test (suite must be specified with -s|--suite)");
    puts("  -q|--quiet    display minimal output");
    puts("  -v|--verbose  display verbose output");
    puts("  -h|--help     displays this message");
    return 0;
  }

  CU_ERROR_CHECK(CU_initialize_registry());

  CU_ERROR_CHECK(CU_register_suites((CU_SuiteInfo *)suites));

  CU_basic_set_mode(mode);

  if (suite_name != NULL) {
    CU_pTestRegistry registry = CU_get_registry();
    CU_pSuite suite = CU_get_suite_by_name(suite_name, registry);
    if (suite == NULL) {
      CU_cleanup_registry();
      fprintf(stderr, "No such suite \"%s\"\n", suite_name);
      return -1;
    }

    if (test_name != NULL) {
      CU_pTest test = CU_get_test_by_name(test_name, suite);
      if (test == NULL) {
        CU_cleanup_registry();
        fprintf(stderr, "No such test \"%s\" in suite \"%s\"\n", test_name, suite_name);
        return -1;
      }

      CU_ERROR_CHECK(CU_basic_run_test(suite, test));
    }
    else
      CU_ERROR_CHECK(CU_basic_run_suite(suite));
  }
  else
    CU_ERROR_CHECK(CU_basic_run_tests());

  CU_basic_show_failures(CU_get_failure_list());
  putchar('\n');

  unsigned int failures = CU_get_number_of_failures();

  CU_cleanup_registry();

  return (int)failures;
}
