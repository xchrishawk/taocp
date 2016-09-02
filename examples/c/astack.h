/*
 * astack.h
 * Chris Vig (chris@invictus.so)
 */

#ifndef ASTACK_H
#define ASTACK_H

/* -- Includes -- */

#include <stdbool.h>

/* -- Types -- */

/* Struct containing a linear array-based stack. */
struct astack;

/* Opaque pointer to the `astack` struct. */
typedef struct astack* astack_t;

/* Type of element held in the `astack`. */
typedef char astack_el;

/* -- Procedures -- */

/* Creates a new array stack with the specified initial capacity. */
astack_t astack_new(size_t capacity, bool expandable);

/* Deletes an array stack. */
void astack_delete(astack_t stack);

/* Gets the number of items in the specified stack. */
size_t astack_count(astack_t stack);

/* Gets the capacity of the specified stack. */
size_t astack_capacity(astack_t stack);

/* Pushes a new element onto the specified stack. */
bool astack_push(astack_t stack, astack_el el);

/* Pops the top element off of the specified stack, if it exists. */
bool astack_pop(astack_t stack, astack_el* out_el);

/* Peeks at the top element on the specified stack, if it exists. */
bool astack_peek(astack_t stack, astack_el* out_el);

#endif /* ASTACK_H */
