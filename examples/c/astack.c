/*
 * astack.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdlib.h>
#include "astack.h"

/* -- Types -- */

struct astack
{
  astack_el* array;
  size_t count;
  size_t capacity;
  bool expandable;
};

/* -- Procedure Prototypes -- */

static bool astack_resize(astack_t stack, size_t capacity);

/* -- Procedures -- */

astack_t astack_new(size_t capacity, bool expandable)
{
  astack_el* array = (astack_el*)calloc(capacity, sizeof(astack_el));
  if (!array)
    return NULL;

  astack_t stack = (astack_t)malloc(sizeof(struct astack));
  if (!stack)
  {
    free(array);
    return NULL;
  }

  stack->array = array;
  stack->count = 0;
  stack->capacity = capacity;
  stack->expandable = expandable;

  return stack;
}

void astack_delete(astack_t stack)
{
  free(stack->array);
  free(stack);
}

size_t astack_count(astack_t stack)
{
  return stack->count;
}

size_t astack_capacity(astack_t stack)
{
  return stack->capacity;
}

taocp_err astack_push(astack_t stack, astack_el el)
{
  if (stack->count == stack->capacity)
  {
    if (!stack->expandable)
      return TAOCP_ERR_OVERFLOW;

    size_t new_capacity = stack->capacity * 2;
    if (!astack_resize(stack, new_capacity))
      return TAOCP_ERR_MEMORY;
  }

  stack->array[stack->count] = el;
  stack->count++;
  return TAOCP_ERR_OK;
}

taocp_err astack_pop(astack_t stack, astack_el* el)
{
  if (stack->count == 0)
    return TAOCP_ERR_UNDERFLOW;

  *el = stack->array[stack->count - 1];
  stack->count--;
  return TAOCP_ERR_OK;
}

taocp_err astack_peek(astack_t stack, astack_el* el)
{
  if (stack->count == 0)
    return TAOCP_ERR_UNDERFLOW;

  *el = stack->array[stack->count - 1];
  return TAOCP_ERR_OK;
}

/* -- Private Functions -- */

static bool astack_resize(astack_t stack, size_t new_capacity)
{
  astack_el* new_array = (astack_el*)realloc(stack->array, sizeof(astack_el) * new_capacity);
  if (!new_array)
    return false;

  stack->array = new_array;
  stack->capacity = new_capacity;
  return true;
}
