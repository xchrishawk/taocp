/*
 * deque.h
 * Chris Vig (chris@invictus.so)
 */

#ifndef DEQUE_H
#define DEQUE_H

/* -- Includes -- */

#include "taocp_err.h"

/* -- Types -- */

/* Opaque deque struct type. */
struct deque;

/* Pointer to a `deque` struct. */
typedef struct deque* deque_t;

/** Element type stored in deque. */
typedef int deque_el;

/* -- Procedure Prototypes -- */

/* Initializes and returns a new deque. */
deque_t deque_new();

/* Deletes an existing deque. */
void deque_delete(deque_t deque);

/* Gets the number of elements in a deque. */
size_t deque_count(deque_t deque);

/* Pushes an element to the front of the deque. */
taocp_err deque_push_front(deque_t deque, deque_el el);

/* Pops an element from the front of the deque. */
taocp_err deque_pop_front(deque_t deque, deque_el* out_el);

/* Pushes an element to the back of the deque. */
taocp_err deque_push_back(deque_t deque, deque_el el);

/* Pops an element from the back of the deque. */
taocp_err deque_pop_back(deque_t deque, deque_el* out_el);

#endif /* DEQUE_H */
