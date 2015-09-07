#include <stdbool.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
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
  bool list = false, help = false;
  const char * output = "CUnitAutomated";
  const struct option longopts[] = {
    { "list",   no_argument,       (int *)&list, (int)true },
    { "output", required_argument,         NULL,      'o'  },
    { "help",   no_argument,       (int *)&help, (int)true },
    { NULL,     0,                         NULL,      0    }
  };

  opterr = 0;
  int c, longindex;
  while ((c = getopt_long(argc, argv, ":lo:h", longopts, &longindex)) != -1) {
    switch (c) {
      case 'l':
        list = true;
        break;
      case 'o':
        output = optarg;
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
    printf("Usage: %s [-l|--list] [-o|--output=<template>] [-h|--help]\n", argv[0]);
    puts("Where:");
    puts("  -l|--list    lists the tests to a file (default \"CUnitAutomated-Listing.xml\")");
    puts("  -o|--output  sets the filename template to use (tests are listed in "
         "\"<template>-Listing.xml\" while results are placed in \"<template>-Results.xml\")");
    puts("  -h|--help    displays this message");
    return 0;
  }

  CU_ERROR_CHECK(CU_initialize_registry());

  CU_ERROR_CHECK(CU_register_suites((CU_SuiteInfo *)suites));

  CU_set_output_filename(output);

  if (list) {
    CU_ERROR_CHECK(CU_list_tests_to_file());
    return 0;
  }

  CU_automated_run_tests();

  unsigned int failures = CU_get_number_of_failures();

  CU_cleanup_registry();

  return (int)failures;
}
