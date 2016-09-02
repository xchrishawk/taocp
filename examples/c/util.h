#ifndef UTIL_H
#define UTIL_H

/* -- Macros -- */

/* Prints an error message and exits if `cond` is not true. */
#define TAOCP_ASSERT(cond, msg)						\
  (cond ? (void)0 : _taocp_assert_fail(#cond, __FILE__, __LINE__, msg))

/* Prints an error message and exits if `ptr` is null. */
#define TAOCP_ASSERT_NOT_NULL(ptr)			\
  TAOCP_ASSERT(ptr != NULL, #ptr " must not be null")

/* -- Procedure Prototypes -- */

/* Utility function used by `TAOCP_ASSERT`. */
void _taocp_assert_fail(const char* cond, const char* file, int line, const char* msg) __attribute__((noreturn));

#endif /* UTIL_H */
