#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#if defined(__FreeBSD__)
#include <sys/param.h>
#include <osreldate.h>
extern char **environ;
#if __FreeBSD_version >= 1300057
#include <sys/auxv.h>
#else
#include <machine/elf.h>
extern char **environ;
#endif
#endif

char execpath[PATH_MAX];
size_t execpathlen = -1;

int
getexecpath(char *buf, size_t buflen)
{
	if (execpathlen != -1)
		goto cached;

#if defined(__FreeBSD__) && __FreeBSD_version >= 1300057
	char path[PATH_MAX];
	if (elf_aux_info(AT_EXECPATH, path, sizeof(path)) == 0 &&
	    realpath(path, execpath))
		execpathlen = strlen(execpath) + 1;
#elif defined(__FreeBSD__)
	char **p = environ;
	while (*p++ != 0)
		;
	for (Elf_Auxinfo *aux = (Elf_Auxinfo *)p; aux->a_type != AT_NULL; aux++) {
		if (aux->a_type == AT_EXECPATH &&
		    realpath(((char *)aux->a_un.a_ptr, execpath)) {
			execpathlen = strlen(execpath) + 1;
			break;
		}
	}
#endif /* __FreeBSD__ */

#if defined(__linux__)
	char path[PATH_MAX];
	size_t plen = readlink("/proc/self/exe", path, sizeof path);
	if (plen > 0) {
		path[plen] = '\0';
		if (realpath(path, execpath))
			execpathlen = strlen(execpath) + 1;
	}
#endif /* __linux__ */

	if (execpathlen == -1)
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
