/*
 * astack_tests.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <CUnit/CUnit.h>
#include "astack.h"
#include "astack_tests.h"

/* -- Procedure Prototypes -- */

static void test_astack_initialization();
static void test_astack_push();
static void test_astack_pop();
static void test_astack_peek();
static void test_astack_non_expandable();

/* -- Public Procedures -- */

void astack_register_tests()
{
  CU_pSuite suite = CU_add_suite("astack_tests", NULL, NULL);
  CU_add_test(suite, "test_astack_initialization", test_astack_initialization);
  CU_add_test(suite, "test_astack_push", test_astack_push);
  CU_add_test(suite, "test_astack_pop", test_astack_pop);
  CU_add_test(suite, "test_astack_peek", test_astack_peek);
  CU_add_test(suite, "test_astack_non_expandable", test_astack_non_expandable);
}

/* -- Tests -- */

static void test_astack_initialization()
{
  astack_t stack = astack_new(10, true);
  CU_ASSERT_PTR_NOT_NULL(stack);
  CU_ASSERT_EQUAL(astack_count(stack), 0);
  CU_ASSERT_EQUAL(astack_capacity(stack), 10);
  astack_delete(stack);
}

static void test_astack_push()
{
  static const size_t INITIAL_CAPACITY = 3;

  astack_t stack = astack_new(INITIAL_CAPACITY, true);
  CU_ASSERT_PTR_NOT_NULL(stack);

  for (int i = 1; i <= INITIAL_CAPACITY; i++)
  {
    CU_ASSERT(astack_push(stack, 'A'));
    CU_ASSERT_EQUAL(astack_count(stack), i);
    CU_ASSERT_EQUAL(astack_capacity(stack), INITIAL_CAPACITY);
  }

  CU_ASSERT(astack_push(stack, 'B'));
  CU_ASSERT_EQUAL(astack_count(stack), INITIAL_CAPACITY + 1);
  CU_ASSERT_EQUAL(astack_capacity(stack), INITIAL_CAPACITY * 2);

  astack_delete(stack);
}

static void test_astack_pop()
{
  static const char START_CHAR = 'A';
  static const char END_CHAR = 'Z';

  astack_t stack = astack_new(5, true);

  /* push alphabet onto stack */
  for (char c = START_CHAR; c <= END_CHAR; c++)
  {
    CU_ASSERT(astack_push(stack, c));
    CU_ASSERT_EQUAL(astack_count(stack), c - START_CHAR + 1);
  }

  /* verify alphabet is popped off in reverse order */
  for (char c = END_CHAR; c >= START_CHAR; c--)
  {
    char tmp;
    CU_ASSERT(astack_pop(stack, &tmp));
    CU_ASSERT_EQUAL(tmp, c);
    CU_ASSERT_EQUAL(astack_count(stack), c - START_CHAR);
  }

  /* verify stack is empty */
  CU_ASSERT_EQUAL(astack_count(stack), 0);

  /* verify we can't pop from an empty stack */
  char notused;
  CU_ASSERT_FALSE(astack_pop(stack, &notused));

  astack_delete(stack);
}

static void test_astack_peek()
{
  astack_t stack = astack_new(5, true);

  static const char CHAR = 'X';

  /* push char onto stack */
  CU_ASSERT(astack_push(stack, CHAR));
  CU_ASSERT_EQUAL(astack_count(stack), 1);

  /* verify we can peek without modifying the stack */
  char tmp;
  CU_ASSERT(astack_peek(stack, &tmp));
  CU_ASSERT_EQUAL(tmp, CHAR);
  CU_ASSERT_EQUAL(astack_count(stack), 1);

  /* verify we can't peek when stack is empty */
  CU_ASSERT(astack_pop(stack, &tmp));
  CU_ASSERT_EQUAL(astack_count(stack), 0);
  CU_ASSERT_FALSE(astack_peek(stack, &tmp));

  astack_delete(stack);
}

static void test_astack_non_expandable()
{
  astack_t stack = astack_new(3, false);

  CU_ASSERT(astack_push(stack, 'A'));
  CU_ASSERT(astack_push(stack, 'B'));
  CU_ASSERT(astack_push(stack, 'C'));
  CU_ASSERT_FALSE(astack_push(stack, 'D'));

  astack_delete(stack);
}
