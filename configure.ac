#
# Copyright (c) 2014 Brent Cook
# Parts based on configure.ac from Portable OpenNTPD:
# Copyright (c) 2004-2008 Darren Tucker
# which itself was based on configure.ac from OpenSSH:
# Copyright (c) 1999-2004 Damien Miller
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

AC_INIT([OpenNTPD], m4_esyscmd([tr -d '\n' < VERSION]))

AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_SUBST([USER_CFLAGS], "$CFLAGS")
CFLAGS="$CFLAGS -Wall -std=gnu99 -g"

case $host_os in
	*darwin*)
		HOST_OS=darwin
		AC_DEFINE(SETEUID_BREAKS_SETUID,[],[setuid after seteuid does not work])
		AC_DEFINE(BROKEN_SETREUID,[], [Broken setreuid])
		AC_DEFINE(BROKEN_SETREGID,[], [Broken setregid])
		AC_DEFINE(YYSTYPE_IS_DECLARED,[], [Broken bison])
		AC_DEFINE([SPT_TYPE], [SPT_REUSEARGV])
		;;
	*freebsd*)
		HOST_OS=freebsd
		AC_SUBST([PROG_LDADD], ['-lthr'])
		;;
	*linux*)
		HOST_OS=linux
		CFLAGS="$CFLAGS -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_SOURCE -D_GNU_SOURCE"
		AC_DEFINE([SPT_TYPE], [SPT_REUSEARGV])
		;;
	*netbsd*)
		HOST_OS=netbsd
		;;
	*openbsd*)
		AC_DEFINE([HAVE_ATTRIBUTE__BOUNDED__], [1], [OpenBSD has __bounded__])
		AC_DEFINE([HAVE_ATTRIBUTE__DEAD], [1], [OpenBSD has __dead])
		;;
	*solaris*)
		HOST_OS=solaris
		CFLAGS="$CFLAGS -D__EXTENSIONS__ -D_XOPEN_SOURCE=600 -DBSD_COMP"
		AC_SUBST([PLATFORM_LDADD], ['-lnsl -lsocket'])
		;;
	*) ;;
esac

AM_CONDITIONAL([HOST_DARWIN],  [test x$HOST_OS = xdarwin])
AM_CONDITIONAL([HOST_FREEBSD], [test x$HOST_OS = xfreebsd])
AM_CONDITIONAL([HOST_LINUX],   [test x$HOST_OS = xlinux])
AM_CONDITIONAL([HOST_NETBSD],  [test x$HOST_OS = xnetbsd])
AM_CONDITIONAL([HOST_SOLARIS], [test x$HOST_OS = xsolaris])

AC_CHECK_FUNC([dl_iterate_phdr],,
	[AC_SEARCH_LIBS([dl_iterate_phdr],[dl])])

AC_PROG_CC
AC_PROG_CC_STDC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
AC_PROG_YACC

save_cflags="$CFLAGS"
CFLAGS=-Wno-pointer-sign
AC_MSG_CHECKING([whether CC supports -Wno-pointer-sign])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([])],
	[AC_MSG_RESULT([yes])]
	[AM_CFLAGS=-Wno-pointer-sign],
	[AC_MSG_RESULT([no])]
)
CFLAGS="$save_cflags $AM_CFLAGS"

AC_MSG_CHECKING([if compiling with clang])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [[
#ifndef __clang__
	not clang
#endif
	]])],
	[AC_MSG_RESULT([yes])]
	[CLANG_FLAGS=-Qunused-arguments],
	[AC_MSG_RESULT([no])]
)
CFLAGS="$CFLAGS $CLANG_CFLAGS"
LDFLAGS="$LDFLAGS $CLANG_FLAGS"

# check functions that are expected to be in libc
AC_CHECK_FUNCS([adjfreq ntp_adjtime adjtimex])
AC_CHECK_FUNCS([arc4random arc4random_uniform asprintf explicit_bzero])
AC_CHECK_FUNCS([getentropy memmem poll reallocarray])
AC_CHECK_FUNCS([setproctitle setgroups])
AC_CHECK_FUNCS([setregid setresgid setreuid setresuid])
AC_CHECK_FUNCS([strlcat strlcpy strtonum])

# check auxiliary libraries that might contain other functions
AC_SEARCH_LIBS([arc4random], [crypto])
AC_SEARCH_LIBS([clock_getres],[rt posix4])
AC_SEARCH_LIBS([clock_gettime],[rt posix4])
AC_SEARCH_LIBS([ibuf_open], [util])
AC_SEARCH_LIBS([MD5Init], [md md5])
AC_SEARCH_LIBS([SHA512Init], [md])

AC_CHECK_FUNCS([arc4random ibuf_open MD5Init SHA512Init])
AC_CHECK_FUNCS([clock_gettime clock_getres])

# Share test results with automake
AM_CONDITIONAL([HAVE_ADJFREQ], [test "x$ac_cv_func_adjfreq" = xyes])
AM_CONDITIONAL([HAVE_ARC4RANDOM], [test "x$ac_cv_func_arc4random" = xyes])
AM_CONDITIONAL([HAVE_ARC4RANDOM_UNIFORM], [test "x$ac_cv_func_arc4random_uniform" = xyes])
AM_CONDITIONAL([HAVE_ASPRINTF], [test "x$ac_cv_func_asprintf" = xyes])
AM_CONDITIONAL([HAVE_CLOCK_GETRES], [test "x$ac_cv_func_clock_getres" = xyes])
AM_CONDITIONAL([HAVE_CLOCK_GETTIME], [test "x$ac_cv_func_clock_gettime" = xyes])
AM_CONDITIONAL([HAVE_EXPLICIT_BZERO], [test "x$ac_cv_func_explicit_bzero" = xyes])
AM_CONDITIONAL([HAVE_GETENTROPY], [test "x$ac_cv_func_getentropy" = xyes])
AM_CONDITIONAL([HAVE_IMSG], [test "x$ac_cv_func_ibuf_open" = xyes])
AM_CONDITIONAL([HAVE_MD5], [test "x$ac_cv_func_MD5Init" = xyes])
AM_CONDITIONAL([HAVE_MEMMEM], [test "x$ac_cv_func_memmem" = xyes])
AM_CONDITIONAL([HAVE_POLL], [test "x$ac_cv_func_poll" = xyes])
AM_CONDITIONAL([HAVE_REALLOCARRAY], [test "x$ac_cv_func_reallocarray" = xyes])
AM_CONDITIONAL([HAVE_SETGROUPS], [test "x$ac_cv_func_setgroups" = xyes])
AM_CONDITIONAL([HAVE_SETRESGID], [test "x$ac_cv_func_setresgid" = xyes])
AM_CONDITIONAL([HAVE_SETRESUID], [test "x$ac_cv_func_setresuid" = xyes])
AM_CONDITIONAL([HAVE_SETPROCTITLE], [test "x$ac_cv_func_setproctitle" = xyes])
AM_CONDITIONAL([HAVE_SHA512], [test "x$ac_cv_func_SHA512Init" = xyes])
AM_CONDITIONAL([HAVE_STRLCAT], [test "x$ac_cv_func_strlcat" = xyes])
AM_CONDITIONAL([HAVE_STRLCPY], [test "x$ac_cv_func_strlcpy" = xyes])
AM_CONDITIONAL([HAVE_STRTONUM], [test "x$ac_cv_func_strtonum" = xyes])

# overrides for arc4random implementations with known issues
AM_CONDITIONAL([HAVE_ARC4RANDOM],
	[test "x$HOST_OS" != xdarwin \
	   -a "x$HOST_OS" != xfreebsd \
	   -a "x$HOST_OS" != xnetbsd \
	   -a "x$ac_cv_func_arc4random" = xyes])
AM_CONDITIONAL([HAVE_ARC4RANDOM_UNIFORM],
	[test "x$HOST_OS" != xdarwin \
	   -a "x$HOST_OS" != xfreebsd \
	   -a "x$HOST_OS" != xnetbsd \
	   -a "x$ac_cv_func_arc4random_uniform" = xyes])

AC_CACHE_CHECK([if libc defines __progname], ac_cv_libc_defines___progname, [
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[]],
                [[ extern char *__progname; printf("%s", __progname); ]])],
        [ ac_cv_libc_defines___progname="yes" ],
        [ ac_cv_libc_defines___progname="no"
        ])
])
if test "x$ac_cv_libc_defines___progname" = "xyes" ; then
        AC_DEFINE([HAVE___PROGNAME], [1], [Define if libc defines __progname])
fi

AC_CACHE_CHECK([whether va_copy exists], ac_cv_have_va_copy, [
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <stdarg.h>
va_list x,y;
		]], [[ va_copy(x,y); ]])],
	[ ac_cv_have_va_copy="yes" ],
	[ ac_cv_have_va_copy="no"
	])
])
if test "x$ac_cv_have_va_copy" = "xyes" ; then
	AC_DEFINE([HAVE_VA_COPY], [1], [Define if va_copy exists])
fi

AC_CACHE_CHECK([whether __va_copy exists], ac_cv_have___va_copy, [
	AC_LINK_IFELSE([AC_LANG_PROGRAM([[
#include <stdarg.h>
va_list x,y;
		]], [[ __va_copy(x,y); ]])],
	[ ac_cv_have___va_copy="yes" ], [ ac_cv_have___va_copy="no"
	])
])
if test "x$ac_cv_have___va_copy" = "xyes" ; then
	AC_DEFINE([HAVE___VA_COPY], [1], [Define if __va_copy exists])
fi

AC_CHECK_HEADERS([err.h md5.h sha2.h])
AC_CHECK_HEADERS([sys/sensors.h],
	AM_CONDITIONAL(HAVE_SENSORS, true),
	AM_CONDITIONAL(HAVE_SENSORS, false)
)

AC_CHECK_MEMBERS([struct sockaddr_in.sin_len], , ,
	[ #include <netdb.h>
	  #include <netinet/in.h>
	  #include <sys/socket.h> ]
)

AC_ARG_WITH(privsep-user,
	[  --with-privsep-user=user Specify privilege separation user],
	[ AC_DEFINE_UNQUOTED(NTPD_USER, "$withval",
	    [Unprivileged userid])
	  PRIVSEP_USER=$withval ],
	[ PRIVSEP_USER=_ntp ]
)
AC_SUBST(PRIVSEP_USER)

AC_ARG_WITH(privsep-path,
	[  --with-privsep-path=path Specify privilege separation chroot path],
	[ AC_DEFINE_UNQUOTED(NTPD_CHROOT_DIR, "$withval",
	    [Privilege separation chroot path])
	  PRIVSEP_PATH=$withval ],
	[ PRIVSEP_PATH=/var/empty ]
)
AC_SUBST(PRIVSEP_PATH)

AC_CONFIG_FILES([
	Makefile
	include/Makefile
])

AC_OUTPUT
