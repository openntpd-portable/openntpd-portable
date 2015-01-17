/*
 * Public domain
 * md5.h compatibility shim
 */

#ifdef HAVE_MD5_H
#include_next <md5.h>
#else

#if defined(__cplusplus)
#define	__BEGIN_DECLS	extern "C" {
#define	__END_DECLS	};
#else
#define	__BEGIN_DECLS
#define	__END_DECLS
#endif

#include "md5_openbsd.h"
#endif
