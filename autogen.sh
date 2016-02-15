#!/bin/sh
set -e

./update.sh
mkdir -p m4
rm -fr autom4te.cache
autoreconf -i
chmod -R u+w .
curl 'http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD' > config.guess
curl 'http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.sub;hb=HEAD' > config.sub
