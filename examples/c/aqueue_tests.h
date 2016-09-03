/*
 * aqueue_tests.h
 * Chris Vig (chris@invictus.so)
 */

#ifndef AQUEUE_TESTS_H
#define AQUEUE_TESTS_H

#ifndef LIBTAOCP_TEST
#error This file is used for unit testing only!
#endif

/* -- Procedure Prototypes -- */

/* Registers tests for the `aqueue` module. */
void aqueue_register_tests();

#endif /* AQUEUE_TESTS_H */
