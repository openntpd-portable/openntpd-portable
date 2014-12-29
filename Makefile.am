AM_CPPFLAGS = -I$(top_srcdir)/include
SUBDIRS = include

ACLOCAL_AMFLAGS = -Im4
EXTRA_DIST = VERSION
CLEANFILES = parse.c

sbin_PROGRAMS = ntpd
noinst_LTLIBRARIES = libcompat.la libcompatnoopt.la
dist_man_MANS = ntpctl.8 ntpd.8 ntpd.conf.5

ntpd_CFLAGS = $(CFLAGS) $(USER_CFLAGS)
ntpd_LDADD = $(PLATFORM_LDADD) $(PROG_LDADD) libcompat.la libcompatnoopt.la

ntpd_SOURCES = client.c
ntpd_SOURCES += config.c
ntpd_SOURCES += control.c
ntpd_SOURCES += log.c
ntpd_SOURCES += ntp.c
ntpd_SOURCES += ntp.h
ntpd_SOURCES += ntp_dns.c
ntpd_SOURCES += ntp_msg.c
ntpd_SOURCES += ntpd.c
ntpd_SOURCES += ntpd.h
ntpd_SOURCES += parse.y
if !HAVE_ADJFREQ
ntpd_SOURCES += bsd-adjfreq.c
endif
if HAVE_SENSORS
ntpd_SOURCES += sensors.c
else
ntpd_SOURCES += fake-sensors.c
endif
ntpd_SOURCES += server.c
ntpd_SOURCES += util.c

install-exec-hook:
	ln -f $(DESTDIR)$(sbindir)/ntpd $(DESTDIR)$(sbindir)/ntpctl
uninstall-local:
	-rm -f $(DESTDIR)$(sbindir)/ntpctl

# compatibility functions that need to be built without optimizations
libcompatnoopt_la_CFLAGS = -O0
libcompatnoopt_la_SOURCES =

if !HAVE_EXPLICIT_BZERO
libcompatnoopt_la_SOURCES += compat/explicit_bzero.c
endif

# other compatibility functions
libcompat_la_CFLAGS = $(CFLAGS) $(USER_CFLAGS)
libcompat_la_SOURCES =
libcompat_la_LIBADD = $(PLATFORM_LDADD)


if !HAVE_SETPROCTITLE
libcompat_la_SOURCES += compat/setproctitle.c
endif

if !HAVE_STRLCAT
libcompat_la_SOURCES += compat/strlcat.c
endif

if !HAVE_STRLCPY
libcompat_la_SOURCES += compat/strlcpy.c
endif

if !HAVE_STRNDUP
libcompat_la_SOURCES += compat/strndup.c
# the only user of strnlen is strndup, so only build it if needed
if !HAVE_STRNLEN
libcompat_la_SOURCES += compat/strnlen.c
endif
endif

if !HAVE_STRTONUM
libcompat_la_SOURCES += compat/strtonum.c
endif

if !HAVE_ASPRINTF
libcompat_la_SOURCES += compat/bsd-asprintf.c
endif

if !HAVE_REALLOCARRAY
libcompat_la_SOURCES += compat/reallocarray.c
endif

if !HAVE_MD5
libcompat_la_SOURCES += compat/md5.c
endif

if !HAVE_IMSG
libcompat_la_SOURCES += compat/imsg.c
libcompat_la_SOURCES += compat/imsg-buffer.c
endif

if !HAVE_ARC4RANDOM
libcompat_la_SOURCES += compat/arc4random.c

if !HAVE_GETENTROPY
if HOST_FREEBSD
libcompat_la_SOURCES += compat/getentropy_freebsd.c
endif
if HOST_LINUX
libcompat_la_SOURCES += compat/getentropy_linux.c
if !HAVE_SHA512
libcompat_la_SOURCES += compat/sha2.c
endif
endif
if HOST_DARWIN
libcompat_la_SOURCES += compat/getentropy_osx.c
if !HAVE_SHA512
libcompat_la_SOURCES += compat/sha2.c
endif
endif
if HOST_SOLARIS
libcompat_la_SOURCES += compat/getentropy_solaris.c
if !HAVE_SHA512
libcompat_la_SOURCES += compat/sha2.c
endif
endif
endif
endif

if !HAVE_ARC4RANDOM_UNIFORM
libcompat_la_SOURCES += compat/arc4random_uniform.c
endif

noinst_HEADERS = compat/arc4random.h
noinst_HEADERS += compat/arc4random_freebsd.h
noinst_HEADERS += compat/arc4random_linux.h
noinst_HEADERS += compat/arc4random_osx.h
noinst_HEADERS += compat/arc4random_solaris.h
noinst_HEADERS += compat/arc4random_win.h
noinst_HEADERS += compat/chacha_private.h
