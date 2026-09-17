/*
 * Copyright (c) 2026 Brent Cook
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

#include <sys/stat.h>

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
	char path[PATH_MAX];
	struct stat sb;

	if (getexecpath(path, sizeof(path)) != 0) {
		fprintf(stderr, "getexecpath: %s\n", strerror(errno));
		return 1;
	}

	printf("got path %s\n", path);

	if (path[0] != '/') {
		fprintf(stderr, "getexecpath: not an absolute path: %s\n", path);
		return 1;
	}

	if (stat(path, &sb) != 0) {
		fprintf(stderr, "getexecpath: stat %s: %s\n", path, strerror(errno));
		return 1;
	}

	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "getexecpath: %s: not a regular file\n", path);
		return 1;
	}

	if (getexecpath(path, 1) == 0 || errno != ERANGE) {
		fprintf(stderr, "getexecpath: expected ERANGE for an undersized buffer\n");
		return 1;
	}

	return 0;
}
