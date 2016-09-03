#ifndef TAOCP_ERR_H
#define TAOCP_ERR_H

/* -- Types -- */

/** Enumeration of error codes. */
typedef int taocp_err;
enum
{
  /** Unable to allocate memory. */
  TAOCP_ERR_MEMORY = -1,

  /** No error. */
  TAOCP_ERR_OK = 0,

  /** Underflow error. */
  TAOCP_ERR_UNDERFLOW = 1,

  /** Overflow error. */
  TAOCP_ERR_OVERFLOW = 2,
};

#endif
