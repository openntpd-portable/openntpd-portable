#
# Copyright (c) 2014 Brent Cook
# Parts based on Makefile.in from Portable OpenNTPD:
# Copyright (c) 2004-2008 Darren Tucker.
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

AM_CPPFLAGS = -I$(top_srcdir)/include
SUBDIRS = include

ACLOCAL_AMFLAGS = -Im4
EXTRA_DIST = VERSION ntpd.conf
CLEANFILES = parse.c

sbin_PROGRAMS = ntpd
noinst_LTLIBRARIES = libcompat.la libcompatnoopt.la
dist_man_MANS = ntpctl.8 ntpd.8 ntpd.conf.5

ntpd_CFLAGS = $(CFLAGS) $(USER_CFLAGS)
ntpd_CFLAGS += -DSYSCONFDIR=\"$(sysconfdir)\"
ntpd_CFLAGS += -DLOCALSTATEDIR=\"$(localstatedir)\"

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
if HAVE_SENSORS
ntpd_SOURCES += sensors.c
else
ntpd_SOURCES += compat/fake-sensors.c
endif
ntpd_SOURCES += server.c
ntpd_SOURCES += util.c

install-exec-hook:
	@ln -f "$(DESTDIR)$(sbindir)/ntpd" "$(DESTDIR)$(sbindir)/ntpctl"
	@if [ ! -d "$(DESTDIR)$(sysconfdir)" ]; then \
		$(INSTALL) -m 755 -d "$(DESTDIR)$(sysconfdir)"; \
	fi
	@if [ ! -d "$(DESTDIR)$(localstatedir)/run" ]; then \
		$(INSTALL) -m 755 -d "$(DESTDIR)$(localstatedir)/run"; \
	fi
	@if [ ! -d "$(DESTDIR)$(localstatedir)/db" ]; then \
		$(INSTALL) -m 755 -d "$(DESTDIR)$(localstatedir)/db"; \
	fi
	@if [ ! -f "$(DESTDIR)$(sysconfdir)/ntpd.conf" ]; then \
		$(INSTALL) -m 644 "$(srcdir)/ntpd.conf" "$(DESTDIR)$(sysconfdir)/ntpd.conf"; \
	else \
		echo "$(DESTDIR)$(sysconfdir)/ntpd.conf already exists, install will not overwrite"; \
	fi
	@if [ ! -d "$(PRIVSEP_PATH)" ]; then \
		echo; \
		echo " Please created a privilege separation directory for ntpd." ; \
		echo " On Linux / BSD systems, this will probably work:"; \
		echo " # mkdir -p \"$(PRIVSEP_PATH)\"" ; \
		echo " # chown 0 \"$(PRIVSEP_PATH)\"" ; \
		echo " # chgrp 0 \"$(PRIVSEP_PATH)\"" ; \
		echo " # chmod 0755 "$(PRIVSEP_PATH)\""" ; \
		echo " For OS X, see INSTALL for alternate instructions" ; \
	fi
	@if egrep "^$(PRIVSEP_USER):" /etc/group >/dev/null; then \
		: ; \
	else \
		echo; \
		echo " Please create a dedicated group for ntpd." ; \
		echo " On Linux / BSD systems, this will probably work:"; \
		echo " # groupadd $(PRIVSEP_USER)" ; \
		echo " For OS X, see INSTALL for alternate instructions" ; \
	fi
	@if egrep "^$(PRIVSEP_USER):" /etc/passwd >/dev/null; then \
		: ; \
	else \
		echo; \
		echo " Please create a dedicated user for ntpd and ensure it can" ; \
		echo " not be used to log in." ; \
		echo " On Linux / BSD systems, this will probably work:" ; \
		echo " # useradd -g $(PRIVSEP_USER) -s /sbin/nologin -d $(PRIVSEP_PATH) -c 'OpenNTP daemon' $(PRIVSEP_USER)" ; \
		echo " For OS X, see INSTALL for alternate instructions" ; \
	fi
	echo

uninstall-local:
	@if cmp -s "$(DESTDIR)$(sysconfdir)/ntpd.conf" "$(srcdir)/ntpd.conf"; then \
		rm -f "$(DESTDIR)$(sysconfdir)/ntpd.conf"; \
	fi
	@rm -f "$(DESTDIR)$(sbindir)/ntpctl"

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

if !HAVE_ADJFREQ
if HOST_FREEBSD
libcompat_la_SOURCES += compat/adjfreq_freebsd.c
endif
if HOST_LINUX
libcompat_la_SOURCES += compat/adjfreq_linux.c
endif
if HOST_DARWIN
libcompat_la_SOURCES += compat/adjfreq_osx.c
endif
if HOST_SOLARIS
libcompat_la_SOURCES += compat/adjfreq_solaris.c
endif
endif

if !HAVE_ASPRINTF
libcompat_la_SOURCES += compat/bsd-asprintf.c
endif

if !HAVE_CLOCK_GETRES
libcompat_la_SOURCES += compat/clock_getres.c
endif

if !HAVE_CLOCK_GETTIME
if HOST_DARWIN
libcompat_la_SOURCES += compat/clock_gettime_osx.c
endif
endif

if !HAVE_IMSG
libcompat_la_SOURCES += compat/imsg.c
libcompat_la_SOURCES += compat/imsg-buffer.c
endif

if !HAVE_MD5
libcompat_la_SOURCES += compat/md5.c
endif

if !HAVE_REALLOCARRAY
libcompat_la_SOURCES += compat/reallocarray.c
endif

if !HAVE_SETPROCTITLE
libcompat_la_SOURCES += compat/setproctitle.c
endif

if !HAVE_STRLCAT
libcompat_la_SOURCES += compat/strlcat.c
endif

if !HAVE_STRLCPY
libcompat_la_SOURCES += compat/strlcpy.c
endif

if !HAVE_STRTONUM
libcompat_la_SOURCES += compat/strtonum.c
endif

if !HAVE_SETRESGID
libcompat_la_SOURCES += compat/bsd-setresgid.c
endif

if !HAVE_SETRESUID
libcompat_la_SOURCES += compat/bsd-setresuid.c
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
