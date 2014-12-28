#!/usr/bin/env bash
set -e

openntpd_version=`cat VERSION`

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "$OPENNTPD_GIT" ]; then
		git clone https://github.com/openntpd-portable/openbsd.git
	else
		git clone $OPENNTPD_GIT/openbsd
	fi
fi
#(cd openbsd
# git checkout master
# git pull --rebase)

# setup source paths
dir=`pwd`
libc_inc=$dir/openbsd/src/include
libc_src=$dir/openbsd/src/lib/libc
libcrypto_src=$dir/openbsd/src/lib/libcrypto
libutil_src=$dir/openbsd/src/lib/libutil
ntpd_src=$dir/openbsd/src/usr.sbin/ntpd

CP='cp -p'

cp $libc_inc/md5.h include/
cp $libutil_src/imsg.h include/
cp $libutil_src/imsg.c compat/
cp $libutil_src/imsg-buffer.c compat/
(cd compat; patch -p0 < imsg.patch)

for i in explicit_bzero.c strlcpy.c strlcat.c strndup.c strnlen.c; do
	$CP $libc_src/string/$i compat
done
$CP $libc_src/stdlib/reallocarray.c compat
$CP $libc_src/stdlib/strtonum.c compat
$CP $libc_src/crypt/arc4random.c compat
$CP $libc_src/crypt/arc4random_uniform.c compat
$CP $libc_src/crypt/chacha_private.h compat
$CP $libc_src/hash/md5.c compat
$CP $libcrypto_src/crypto/getentropy_*.c compat
$CP $libcrypto_src/crypto/arc4random_*.h compat

for i in client.c config.c control.c log.c ntp.c ntp.h ntp_dns.c ntp_msg.c \
	ntpd.c ntpd.h parse.y sensors.c server.c util.c \
	ntpctl.8 ntpd.8 ntpd.conf.5 ; do
	cp $ntpd_src/$i .
done
patch -p0 < client.patch
patch -p0 < config.patch
patch -p0 < ntp.patch
patch -p0 < ntpd.patch
patch -p0 < parse.patch
patch -p0 < server.patch
patch -p0 < util.patch
