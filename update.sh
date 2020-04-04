#!/bin/sh
set -e

openbsd_branch=`cat OPENBSD_BRANCH`
openntpd_version=`cat VERSION`

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "${OPENNTPD_GIT}" ]; then
		git clone https://github.com/openntpd-portable/openntpd-openbsd.git openbsd
	else
		git clone "${OPENNTPD_GIT}/openbsd"
	fi
fi
(cd openbsd
 git fetch
 git checkout "${openbsd_branch}"
 git pull --rebase)

# setup source paths
dir=`pwd`
patches="${dir}/patches"
etc_src="${dir}/openbsd/src/etc"
libc_inc="${dir}/openbsd/src/include"
libc_src="${dir}/openbsd/src/lib/libc"
arc4random_src="${dir}/openbsd/src/lib/libcrypto/arc4random"
libutil_src="${dir}/openbsd/src/lib/libutil"
ntpd_src="${dir}/openbsd/src/usr.sbin/ntpd"

do_cp_libc() {
	sed "/DEF_WEAK/d" < "${1}" > "${2}"/`basename "${1}"`
}
CP_LIBC='do_cp_libc'
CP='cp -p'
PATCH='patch -p0 -s'

${CP} "${etc_src}/ntpd.conf" ./
sed '/DECLS/d' "${libc_inc}/md5.h" > include/md5.h
sed '/DECLS/d' "${libc_inc}/sha2.h" > include/sha2_openbsd.h
${CP} "${libutil_src}/imsg.h" include/
${CP} "${libutil_src}/imsg.c" compat/
${CP} "${libutil_src}/imsg-buffer.c" compat/
(cd compat; ${PATCH} < "${patches}/patch-imsg.c")

for i in explicit_bzero.c strlcpy.c strlcat.c; do
	${CP_LIBC} "${libc_src}/string/${i}" compat
done
${CP_LIBC} "${libc_src}/stdlib/reallocarray.c" compat
${CP_LIBC} "${libc_src}/stdlib/recallocarray.c" compat
${CP_LIBC} "${libc_src}/stdlib/strtonum.c" compat
${CP_LIBC} "${libc_src}/crypt/arc4random.c" compat
${CP_LIBC} "${libc_src}/crypt/arc4random_uniform.c" compat
${CP_LIBC} "${libc_src}/crypt/chacha_private.h" compat
${CP_LIBC} "${libc_src}/hash/md5.c" compat
${CP_LIBC} "${libc_src}/hash/sha2.c" compat
for i in "${arc4random_src}"/getentropy_*.c; do
	sed -e 's/openssl\/sha.h/sha2.h/' < "${i}" > compat/`basename "${i}"`
done
${CP} "${arc4random_src}"/arc4random_*.h compat

for i in client.c config.c constraint.c control.c log.c log.h ntp.c ntp.h \
	ntp_dns.c ntp_msg.c ntpd.c ntpd.h parse.y sensors.c server.c util.c \
	ntpctl.8 ntpd.8 ntpd.conf.5 ; do
	file=`basename ${i}`
	echo Copying ${file}
	${CP} "${ntpd_src}/${i}" src
done

(cd src
for i in ../patches/*.patch; do
	echo Patching ${i}
	${PATCH} -p4 < "${i}"
done
)
