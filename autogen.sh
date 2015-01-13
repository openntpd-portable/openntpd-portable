#!/bin/sh
set -e

./update.sh
mkdir -p m4
rm -fr autom4te.cache
autoreconf -i
