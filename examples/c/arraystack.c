/* -- Includes -- */

#include <assert.h>
#include <stdlib.h>

#include "arraystack.h"
#include "util.h"

/* -- Types -- */

struct arraystack
{
  arraystack_el* array;
  size_t count;
  size_t capacity;
};

/* -- Procedures -- */

arraystack_t arraystack_new(size_t init_capacity)
{
  arraystack_el* array = (arraystack_el*)calloc(init_capacity, sizeof(arraystack_el));
  TAOCP_ASSERT_NOT_NULL(array);

  arraystack_t stack = (arraystack_t)malloc(sizeof(struct arraystack));
  TAOCP_ASSERT_NOT_NULL(stack);

  stack->array = array;
  stack->count = 0;
  stack->capacity = init_capacity;

  return stack;
}

void arraystack_delete(arraystack_t stack)
{
  free(stack->array);
  free(stack);
}

size_t arraystack_count(arraystack_t stack)
{
  return stack->count;
}

size_t arraystack_capacity(arraystack_t stack)
{
  return stack->capacity;
}

void arraystack_push(arraystack_t stack, arraystack_el el)
{
  if (stack->count == stack->capacity)
  {
    size_t new_capacity = stack->capacity * 2;
    arraystack_el* new_array = realloc(stack->array, new_capacity);
    TAOCP_ASSERT_NOT_NULL(new_array);

    stack->array = new_array;
    stack->capacity = new_capacity;
  }

  stack->array[stack->count] = el;
  stack->count++;
}

arraystack_el arraystack_pop(arraystack_t stack)
{
  TAOCP_ASSERT(stack->count != 0, "Array stack underflow!");
  arraystack_el el = stack->array[stack->count - 1];
  stack->count--;
  return el;
}

arraystack_el arraystack_peek(arraystack_t stack)
{
  TAOCP_ASSERT(stack->count != 0, "Array stack underflow!");
  return stack->array[stack->count - 1];
}
