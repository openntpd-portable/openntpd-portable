#!/bin/sh
set -e

openbsd_branch=`cat OPENBSD_BRANCH`
openntpd_version=`cat VERSION`

# pull in latest upstream code
echo "pulling upstream openbsd source"
if [ ! -d openbsd ]; then
	if [ -z "$OPENNTPD_GIT" ]; then
		git clone https://github.com/openntpd-portable/openntpd-openbsd.git openbsd
	else
		git clone $OPENNTPD_GIT/openbsd
	fi
fi
(cd openbsd
 git checkout $openbsd_branch
 git pull --rebase)

# setup source paths
dir=`pwd`
patches=$dir/patches
libc_inc=$dir/openbsd/src/include
libc_src=$dir/openbsd/src/lib/libc
libcrypto_src=$dir/openbsd/src/lib/libcrypto
libutil_src=$dir/openbsd/src/lib/libutil
ntpd_src=$dir/openbsd/src/usr.sbin/ntpd

CP='cp -p'
PATCH='patch -p0 -s'

sed '/DECLS/d' $libc_inc/md5.h > include/md5.h
sed '/DECLS/d' $libc_inc/sha2.h > include/sha2_openbsd.h
cp $libutil_src/imsg.h include/
cp $libutil_src/imsg.c compat/
cp $libutil_src/imsg-buffer.c compat/
(cd compat; $PATCH < $patches/patch-imsg.c)

for i in explicit_bzero.c strlcpy.c strlcat.c; do
	$CP $libc_src/string/$i compat
done
$CP $libc_src/stdlib/reallocarray.c compat
$CP $libc_src/stdlib/strtonum.c compat
$CP $libc_src/crypt/arc4random.c compat
$CP $libc_src/crypt/arc4random_uniform.c compat
$CP $libc_src/crypt/chacha_private.h compat
$CP $libc_src/hash/md5.c compat
$CP $libc_src/hash/sha2.c compat
for i in $libcrypto_src/crypto/getentropy_*.c; do
	sed -e 's/openssl\/sha.h/sha2.h/' < $i > compat/`basename $i`
done
$CP $libcrypto_src/crypto/arc4random_*.h compat

for i in client.c config.c constraint.c control.c log.c log.h ntp.c ntp.h \
	ntp_dns.c ntp_msg.c ntpd.c ntpd.h parse.y sensors.c server.c util.c \
	ntpctl.8 ntpd.8 ntpd.conf.5 ; do
	file=`basename $i`
	echo Copying $file
	$CP $ntpd_src/$i src
done

(cd src
for i in ../patches/*.patch; do
	echo Patching $i
	$PATCH -p4 < $i
done
)
