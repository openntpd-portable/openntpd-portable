/*
 * Public domain
 * unistd.h compatibility shim
 */

#include_next <unistd.h>

#ifndef LIBCOMPAT_UNISTD_H
#define LIBCOMPAT_UNISTD_H

#ifndef HAVE_GETENTROPY
int getentropy(void *buf, size_t buflen);
#endif

#include <grp.h>

#ifndef HAVE_SETGROUPS
int setgroups(int ngroups, const gid_t *gidset);
#endif

#endif
