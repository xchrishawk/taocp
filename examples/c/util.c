/* -- Includes -- */

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/* -- Procedures -- */

void _taocp_assert_fail(const char* cond, const char* file, int line, const char* msg)
{
  fprintf(stderr, "* Assertion failed: %s (%s line %d)\n%s\n", cond, file, line, msg);
  exit(1);
}
