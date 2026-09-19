/*
 * Copyright (c) 2026, Theo de Raadt <deraadt@openbsd.org>
 * Copyright (c) 2026, Brent Cook <bcook@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static char execpath[PATH_MAX];
static size_t execpathlen = -1;

#if defined(__FreeBSD__)

#include <sys/param.h>
#include <osreldate.h>

extern char **environ;

#if __FreeBSD_version >= 1300057
#include <sys/auxv.h>
#else
#include <machine/elf.h>
#endif

static void
_getexecpath(void)
{
	char path[PATH_MAX];
	size_t len = sizeof(path);
#if __FreeBSD_version >= 1300057
	if (elf_aux_info(AT_EXECPATH, path, len) == 0 && realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
#else
	char **p = environ;
	while (*p++ != NULL)
		;
	for (Elf_Auxinfo *aux = (Elf_Auxinfo *)p;
		aux->a_type != AT_NULL; aux++) {
		if (aux->a_type == AT_EXECPATH &&
			realpath((char *)aux->a_un.a_ptr, execpath)) {
			execpathlen = strlen(execpath) + 1;
			break;
		}
	}
#endif
}
#endif /* __FreeBSD__ */

#if defined(__linux__) || defined(__CYGWIN__) || defined(__sun) || defined(_AIX)
/*
 * Resolve a procfs symlink that points at the running executable.
 */
static int
_getexecpath_readlink(const char *path)
{
	char buf[PATH_MAX];
	ssize_t len;
	len = readlink(path, buf, sizeof(buf) - 1);
	if (len <= 0)
		return -1;
	buf[len] = '\0';
	if (realpath(buf, execpath) == NULL)
		return -1;
	execpathlen = strlen(execpath) + 1;
	return 0;
}

#if defined(__linux__) || defined(__CYGWIN__)
static void
_getexecpath(void)
{
	_getexecpath_readlink("/proc/self/exe");
}
#endif

#if defined(__sun)
static void
_getexecpath(void)
{
	char path[PATH_MAX];
	size_t len = sizeof(path);
	snprintf(path, len, "/proc/%d/path/a.out", getpid());
	_getexecpath_readlink(path);
}
#endif

#if defined(_AIX)
static void
_getexecpath(void)
{
	char path[PATH_MAX];
	size_t len = sizeof(path);
	snprintf(path, len, "/proc/%d/object/a.out", getpid());
	_getexecpath_readlink(path);
}
#endif
#endif /* _getexecpath_readlink */

#if defined(__NetBSD__)
#include <sys/param.h>
#include <sys/sysctl.h>
static void
_getexecpath(void)
{
	char path[PATH_MAX];
	size_t len = sizeof(path);
	int mib[4] = {
		CTL_KERN,
		KERN_PROC_ARGS,
		-1,
		KERN_PROC_PATHNAME
	};

	if (sysctl(mib, 4, path, &len, NULL, 0) == 0 && realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
}
#endif

#if defined(__DragonFly__)
#include <sys/param.h>
#include <sys/sysctl.h>
static void
_getexecpath(void)
{
	char path[PATH_MAX];
	size_t len = sizeof(path);
	int mib[4] = {
		CTL_KERN,
		KERN_PROC,
		KERN_PROC_PATHNAME,
		-1
	};

	if (sysctl(mib, 4, path, &len, NULL, 0) == 0 && realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
}
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
static void _getexecpath(void)
{
	char path[PATH_MAX];
	uint32_t len = sizeof(path);
	if (_NSGetExecutablePath(path, &len) == 0 &&
		realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
}
#endif

int
getexecpath(char *buf, size_t buflen)
{
	if (execpathlen != (size_t)-1)
		goto cached;

	_getexecpath();

	if (execpathlen == (size_t)-1)
		execpathlen = 0;

cached:
	if (execpathlen == 0) {			/* previous lookup failed */
		errno = ENOENT;
		return -1;
	}
	if (buflen < execpathlen) {
		errno = ERANGE;
		return -1;
	}
	strlcpy(buf, execpath, buflen);
	return 0;
}
