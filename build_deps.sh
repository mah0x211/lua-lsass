#!/bin/sh

set -e
set -x

cd deps/libsass/
autoreconf -ivf
./configure
make
make check
