/*
 * aqueue.h
 * Chris Vig (chris@invictus.so)
 */

#ifndef AQUEUE_H
#define AQUEUE_H

/* -- Includes -- */

#include <stdbool.h>
#include <stdlib.h>

/* -- Types -- */

struct aqueue;

typedef struct aqueue* aqueue_t;

typedef int aqueue_el;

typedef int aqueue_err;
enum
{
  AQUEUE_ERR_MEMORY = -1,
  AQUEUE_ERR_OK = 0,
  AQUEUE_ERR_UNDERFLOW = 1,
  AQUEUE_ERR_OVERFLOW = 2,
};

/* -- Procedure Prototypes -- */

aqueue_t aqueue_new(size_t capacity, bool expandable);

void aqueue_delete(aqueue_t queue);

size_t aqueue_count(aqueue_t queue);

size_t aqueue_capacity(aqueue_t queue);

aqueue_err aqueue_enqueue(aqueue_t queue, aqueue_el el);

aqueue_err aqueue_dequeue(aqueue_t queue, aqueue_el* out_el);

aqueue_err aqueue_peek(aqueue_t queue, aqueue_el* out_el);

#endif /* AQUEUE_H */
