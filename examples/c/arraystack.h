#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

/* -- Types -- */

struct arraystack;
typedef struct arraystack* arraystack_t;

typedef char arraystack_el;

/* -- Procedure Prototypes -- */

/** Creates a new array stack. */
arraystack_t arraystack_new(size_t init_capacity);

/** Deletes an existing array stack. */
void arraystack_delete(arraystack_t stack);

/** Returns the number of elements in the specified array stack. */
size_t arraystack_count(arraystack_t stack);

/** Returns the capacity of the specified array stack. */
size_t arraystack_capacity(arraystack_t stack);

/** Pushes a new element onto an array stack. */
void arraystack_push(arraystack_t stack, arraystack_el el);

/** Pops an element off of an array stack. */
arraystack_el arraystack_pop(arraystack_t stack);

/** Peeks at the top element on an array stack, without popping it. */
arraystack_el arraystack_peek(arraystack_t stack);

#endif /* ARRAYSTACK_H */
