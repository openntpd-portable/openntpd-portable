/*
 * Public domain
 * tls.h compatibility shim
 */

#ifdef HAVE_LIBTLS
#include_next <tls.h>

#else

#ifndef LIBCOMPAT_LIBTLS_H
#define LIBCOMPAT_LIBTLS_H

#include <sys/types.h>
#include <stdint.h>

static inline int
tls_init(void)
{
	return -1;
}

static inline uint8_t *
tls_load_file(const char *_file, size_t *_len, char *_password)
{
	return NULL;
}

#endif

#endif
