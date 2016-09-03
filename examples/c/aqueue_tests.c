/*
 * aqueue_tests.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdio.h>
#include <CUnit/CUnit.h>
#include "aqueue.h"
#include "aqueue_tests.h"

/* -- Procedure Prototypes -- */

static void test_aqueue_initialization();
static void test_aqueue_enqueue_dequeue();
static void test_aqueue_peek();
static void test_aqueue_resize();

/* -- Public Procedures -- */

void aqueue_register_tests()
{
  CU_pSuite suite = CU_add_suite("aqueue_tests", NULL, NULL);
  CU_add_test(suite, "test_aqueue_initialization", test_aqueue_initialization);
  CU_add_test(suite, "test_aqueue_enqueue_dequeue", test_aqueue_enqueue_dequeue);
  CU_add_test(suite, "test_aqueue_peek", test_aqueue_peek);
  CU_add_test(suite, "test_aqueue_resize", test_aqueue_resize);
}

/* -- Tests -- */

static void test_aqueue_initialization()
{
  static const size_t CAPACITY = 5;
  aqueue_t queue = aqueue_new(CAPACITY, true);

  CU_ASSERT_PTR_NOT_NULL(queue);
  CU_ASSERT_EQUAL(aqueue_count(queue), 0);
  CU_ASSERT_EQUAL(aqueue_capacity(queue), CAPACITY);

  aqueue_delete(queue);
}

static void test_aqueue_enqueue_dequeue()
{
  static const size_t CAPACITY = 5;

  aqueue_t queue = aqueue_new(CAPACITY, false);
  CU_ASSERT_PTR_NOT_NULL(queue);

  /* do this twice to test wraparound */
  for (int test = 0; test < 2; test++)
  {
    CU_ASSERT_EQUAL(aqueue_count(queue), 0);

    /* enqueue */
    for (int i = 1; i <= CAPACITY - 1; i++)
    {
      CU_ASSERT_EQUAL(aqueue_enqueue(queue, i), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(aqueue_count(queue), i);
    }

    CU_ASSERT_EQUAL(aqueue_count(queue), CAPACITY - 1);

    /* dequeue */
    for (int i = 1; i <= CAPACITY - 1; i++)
    {
      int tmp;
      CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);
      CU_ASSERT_EQUAL(aqueue_count(queue), CAPACITY - i - 1);
      CU_ASSERT_EQUAL(tmp, i);
    }

    CU_ASSERT_EQUAL(aqueue_count(queue), 0);
  }

  aqueue_delete(queue);
}

static void test_aqueue_peek()
{
  aqueue_t queue = aqueue_new(5, false);
  CU_ASSERT_PTR_NOT_NULL(queue);

  static const int VALUE = 1;

  CU_ASSERT_EQUAL(aqueue_enqueue(queue, VALUE), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(aqueue_count(queue), 1);

  /* verify we can peek at the first value without modifying the queue */
  int tmp;
  CU_ASSERT_EQUAL(aqueue_peek(queue, &tmp), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(tmp, VALUE);
  CU_ASSERT_EQUAL(aqueue_count(queue), 1);

  /* verify we can't peek when the queue is empty */
  CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(aqueue_peek(queue, &tmp), TAOCP_ERR_UNDERFLOW);

  aqueue_delete(queue);
}

static void test_aqueue_resize()
{
  static const size_t INITIAL_CAPACITY = 5;

  aqueue_t queue = aqueue_new(INITIAL_CAPACITY, true);
  CU_ASSERT_PTR_NOT_NULL(queue);

  int tmp;

  /* move front off of the beginning so we wrap around */
  CU_ASSERT_EQUAL(aqueue_enqueue(queue, 0), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(aqueue_enqueue(queue, 0), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);
  CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);

  /* make sure state is good */
  CU_ASSERT_EQUAL(aqueue_count(queue), 0);
  CU_ASSERT_EQUAL(aqueue_capacity(queue), INITIAL_CAPACITY);

  /* queue up items to fill up the queue */
  int idx;
  for (idx = 1; idx <= INITIAL_CAPACITY; idx++)
  {
    CU_ASSERT_EQUAL(aqueue_enqueue(queue, idx), TAOCP_ERR_OK);
    CU_ASSERT_EQUAL(aqueue_count(queue), idx);
    CU_ASSERT_EQUAL(aqueue_capacity(queue), INITIAL_CAPACITY);
  }

  /* queue one more item to overflow and force a resize */
  CU_ASSERT_EQUAL(aqueue_enqueue(queue, idx), TAOCP_ERR_OK);

  /* verify queue is still in correct order */
  for (idx = 1; idx <= INITIAL_CAPACITY + 1; idx++)
  {
    CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);
    CU_ASSERT_EQUAL(tmp, idx);
    CU_ASSERT_EQUAL(aqueue_count(queue), INITIAL_CAPACITY + 1 - idx);
    CU_ASSERT_EQUAL(aqueue_capacity(queue), INITIAL_CAPACITY * 2);
  }

  /* now do the same thing with it initially aligned at zero */
  for (idx = 1; idx <= (INITIAL_CAPACITY * 2) + 1; idx++)
  {
    CU_ASSERT_EQUAL(aqueue_enqueue(queue, idx), TAOCP_ERR_OK);
    CU_ASSERT_EQUAL(aqueue_count(queue), idx);
  }
  for (idx = 1; idx <= (INITIAL_CAPACITY * 2) + 1; idx++)
  {
    CU_ASSERT_EQUAL(aqueue_dequeue(queue, &tmp), TAOCP_ERR_OK);
    CU_ASSERT_EQUAL(tmp, idx);
  }

  aqueue_delete(queue);
}
