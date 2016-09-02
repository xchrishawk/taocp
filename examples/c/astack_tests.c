/*
 * astack_tests.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <CUnit/CUnit.h>
#include "astack_tests.h"

/* -- Procedure Prototypes -- */

static void astack_sample_test();

/* -- Public Procedures -- */

void astack_register_tests()
{
  CU_pSuite suite = CU_add_suite("astack_tests", NULL, NULL);

  CU_add_test(suite, "astack_sample_test", astack_sample_test);
}

/* -- Tests -- */

static void astack_sample_test()
{
  CU_ASSERT(0);
}
