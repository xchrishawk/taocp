/* -- Includes -- */

#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "astack_tests.h"
#include "aqueue_tests.h"
#include "deque_tests.h"

/* -- Procedures -- */

int main(int argc, char** argv)
{
  CU_initialize_registry();

  astack_register_tests();
  aqueue_register_tests();
  deque_register_tests();

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  bool success = (CU_get_number_of_failures() == 0);
  CU_cleanup_registry();

  return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}
