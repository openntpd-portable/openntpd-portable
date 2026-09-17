#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#if defined(__FreeBSD__)
#include <sys/param.h>
#include <osreldate.h>
extern char **environ;
#if __FreeBSD_version >= 1300057
#include <sys/auxv.h>
#else
#include <machine/elf.h>
#endif
#endif

#if defined(__NetBSD__)
#include <sys/param.h>
#include <sys/sysctl.h>
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

static char execpath[PATH_MAX];
static size_t execpathlen = -1;

#if defined(__linux__) || defined(__CYGWIN__) || defined(__sun) || \
    defined(_AIX)
/*
 * Resolve a procfs symlink that points at the running executable.
 * Returns 0 and fills execpath/execpathlen on success, -1 otherwise.
 */
static int
getexecpath_readlink(const char *path)
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
#endif

int
getexecpath(char *buf, size_t buflen)
{
#if defined(__FreeBSD__) || defined(__sun) || defined(_AIX) || \
    defined(__NetBSD__) || defined(__APPLE__)
	char path[PATH_MAX];
	size_t len = sizeof(path);
#endif

	if (execpathlen != (size_t)-1)
		goto cached;

#if defined(__FreeBSD__) && __FreeBSD_version >= 1300057
	if (elf_aux_info(AT_EXECPATH, path, len) == 0 &&
		realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;

#elif defined(__FreeBSD__)
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
#endif /* __FreeBSD__ */

#if defined(__linux__) || defined(__CYGWIN__)
	getexecpath_readlink("/proc/self/exe");
#endif

#if defined(__sun)
	snprintf(path, len, "/proc/%d/path/a.out", getpid());
	getexecpath_readlink(path);
#endif

#if defined(_AIX)
	snprintf(path, len, "/proc/%d/object/a.out", getpid());
	getexecpath_readlink(path);
#endif

#if defined(__NetBSD__)
	int mib[4];

	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC_ARGS;
	mib[2] = -1;
	mib[3] = KERN_PROC_PATHNAME;
	if (sysctl(mib, 4, path, &len, NULL, 0) == 0 &&
		realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
#endif

#if defined(__APPLE__)
	uint32_t size = len;

	if (_NSGetExecutablePath(path, &size) == 0 &&
		realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
#endif

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
