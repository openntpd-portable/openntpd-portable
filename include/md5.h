/*
 * Public domain
 * md5.h compatibility shim
 */

#ifdef HAVE_MD5_H
#include_next <md5.h>
#else
#include "md5_openbsd.h"
#include <machine/endian.h>
#endif
