/*
 * Public domain
 * sys/cdefs.h compatibility shim
 */

#include_next <sys/cdefs.h>

#ifndef __weak_alias
/*
 * We do not use any of the SHA function aliases that this would provide in
 * OpenNTPD
 */
#define __weak_alias(alias,sym)
#endif
