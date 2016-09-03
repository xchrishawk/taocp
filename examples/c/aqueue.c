/*
 * aqueue.c
 * Chris Vig (chris@invictus.so)
 */

/* -- Includes -- */

#include <stdlib.h>
#include <string.h>
#include "aqueue.h"

/* -- Types -- */

struct aqueue
{
  aqueue_el* array;
  size_t front;
  size_t count;
  size_t capacity;
  bool expandable;
};

/* -- Procedure Prototypes -- */

static bool aqueue_resize(aqueue_t queue, size_t new_capacity);

/* -- Procedures -- */

aqueue_t aqueue_new(size_t capacity, bool expandable)
{
  aqueue_el* array = (aqueue_el*)calloc(capacity, sizeof(aqueue_el));
  if (!array)
    return NULL;

  aqueue_t queue = (aqueue_t)malloc(sizeof(struct aqueue));
  if (!queue)
  {
    free(array);
    return NULL;
  }

  queue->array = array;
  queue->front = 0;
  queue->count = 0;
  queue->capacity = capacity;
  queue->expandable = expandable;

  return queue;
}

void aqueue_delete(aqueue_t queue)
{
  free(queue->array);
  free(queue);
}

size_t aqueue_count(aqueue_t queue)
{
  return queue->count;
}

size_t aqueue_capacity(aqueue_t queue)
{
  return queue->capacity;
}

aqueue_err aqueue_enqueue(aqueue_t queue, aqueue_el el)
{
  if (queue->count == queue->capacity)
  {
    if (!queue->expandable)
      return AQUEUE_ERR_OVERFLOW;

    size_t new_capacity = queue->capacity * 2;
    if (!aqueue_resize(queue, new_capacity))
      return AQUEUE_ERR_MEMORY;
  }

  size_t idx = (queue->front + queue->count) % queue->capacity;
  queue->array[idx] = el;
  queue->count++;
  return AQUEUE_ERR_OK;
}

aqueue_err aqueue_dequeue(aqueue_t queue, aqueue_el* el)
{
  if (queue->count == 0)
    return AQUEUE_ERR_UNDERFLOW;

  *el = queue->array[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->count--;
  return AQUEUE_ERR_OK;
}

aqueue_err aqueue_peek(aqueue_t queue, aqueue_el* el)
{
  if (queue->count == 0)
    return AQUEUE_ERR_UNDERFLOW;

  *el = queue->array[queue->front];
  return AQUEUE_ERR_OK;
}

/* -- Private Procedures -- */

static bool aqueue_resize(aqueue_t queue, size_t new_capacity)
{
  aqueue_el* new_array = (aqueue_el*)calloc(new_capacity, sizeof(aqueue_el));
  if (!new_array)
    return false;

  size_t front_els = queue->capacity - queue->front;
  size_t back_els = (queue->front + queue->count) % queue->capacity;

  memcpy(new_array, queue->array + queue->front, front_els * sizeof(aqueue_el));
  memcpy(new_array + front_els, queue->array, back_els * sizeof(aqueue_el));

  free(queue->array);

  queue->array = new_array;
  queue->front = 0;
  queue->capacity = new_capacity;

  return true;
}
