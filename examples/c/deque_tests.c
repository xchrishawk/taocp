/*
 * deque_tests.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <CUnit/CUnit.h>
#include "deque.h"
#include "deque_tests.h"

/* -- Constants -- */

static const int OUTER_LOOPS = 2;
static const int INNER_LOOPS = 5;

/* -- Procedure Prototypes -- */

static void test_deque_initialization();
static void test_deque_front_stack();
static void test_deque_front_queue();
static void test_deque_back_stack();
static void test_deque_back_queue();

/* -- Public Procedures -- */

void deque_register_tests()
{
  CU_pSuite suite = CU_add_suite("deque_tests", NULL, NULL);
  CU_add_test(suite, "test_deque_initialization", test_deque_initialization);
  CU_add_test(suite, "test_deque_front_stack", test_deque_front_stack);
  CU_add_test(suite, "test_deque_front_queue", test_deque_front_queue);
  CU_add_test(suite, "test_deque_back_stack", test_deque_back_stack);
  CU_add_test(suite, "test_deque_back_queue", test_deque_back_queue);
}

/* -- Tests -- */

static void test_deque_initialization()
{
  deque_t deque = deque_new();

  CU_ASSERT_PTR_NOT_NULL(deque);
  CU_ASSERT_EQUAL(deque_count(deque), 0);

  deque_delete(deque);
}

static void test_deque_front_stack()
{
  deque_t deque = deque_new();
  CU_ASSERT_PTR_NOT_NULL(deque);

  for (int test = 0; test < OUTER_LOOPS; test++)
  {
    CU_ASSERT_EQUAL(deque_count(deque), 0);

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      CU_ASSERT_EQUAL(deque_push_front(deque, i), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(deque_count(deque), i);
    }

    for (int i = INNER_LOOPS; i >= 1; i--)
    {
      int tmp;
      CU_ASSERT_EQUAL(deque_pop_front(deque, &tmp), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(tmp, i);
      CU_ASSERT_EQUAL(deque_count(deque), i - 1);
    }

    int notused;
    CU_ASSERT_EQUAL(deque_pop_front(deque, &notused), TAOCP_ERR_UNDERFLOW);
  }


  deque_delete(deque);
}

static void test_deque_front_queue()
{
  deque_t deque = deque_new();
  CU_ASSERT_PTR_NOT_NULL(deque);

  for (int test = 0; test < OUTER_LOOPS; test++)
  {
    CU_ASSERT_EQUAL(deque_count(deque), 0);

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      CU_ASSERT_EQUAL(deque_push_back(deque, i), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(deque_count(deque), i);
    }

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      int tmp;
      CU_ASSERT_EQUAL(deque_pop_front(deque, &tmp), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(tmp, i);
      CU_ASSERT_EQUAL(deque_count(deque), INNER_LOOPS - i);
    }

    int notused;
    CU_ASSERT_EQUAL(deque_pop_front(deque, &notused), TAOCP_ERR_UNDERFLOW);
  }

  deque_delete(deque);
}

static void test_deque_back_stack()
{
  deque_t deque = deque_new();
  CU_ASSERT_PTR_NOT_NULL(deque);

  for (int test = 0; test < OUTER_LOOPS; test++)
  {
    CU_ASSERT_EQUAL(deque_count(deque), 0);

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      CU_ASSERT_EQUAL(deque_push_back(deque, i), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(deque_count(deque), i);
    }

    for (int i = INNER_LOOPS; i >= 1; i--)
    {
      int tmp;
      CU_ASSERT_EQUAL(deque_pop_back(deque, &tmp), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(tmp, i);
      CU_ASSERT_EQUAL(deque_count(deque), i - 1);
    }

    int notused;
    CU_ASSERT_EQUAL(deque_pop_back(deque, &notused), TAOCP_ERR_UNDERFLOW);
  }

  deque_delete(deque);
}

static void test_deque_back_queue()
{
  deque_t deque = deque_new();
  CU_ASSERT_PTR_NOT_NULL(deque);

  for (int test = 0; test < OUTER_LOOPS; test++)
  {
    CU_ASSERT_EQUAL(deque_count(deque), 0);

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      CU_ASSERT_EQUAL(deque_push_front(deque, i), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(deque_count(deque), i);
    }

    for (int i = 1; i <= INNER_LOOPS; i++)
    {
      int tmp;
      CU_ASSERT_EQUAL(deque_pop_back(deque, &tmp), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(tmp, i);
      CU_ASSERT_EQUAL(deque_count(deque), INNER_LOOPS - i);
    }

    int notused;
    CU_ASSERT_EQUAL(deque_pop_back(deque, &notused), TAOCP_ERR_UNDERFLOW);
  }

  deque_delete(deque);
}
