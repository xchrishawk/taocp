/* -- Includes -- */

#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/* -- Procedures -- */

int main(int argc, char** argv)
{
  CU_initialize_registry();
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return (CU_get_number_of_failures() != 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
