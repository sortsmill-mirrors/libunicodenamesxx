#!/bin/sh
#
# You may run this to generate the `configure' script if it is not
# present or needs updating.

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

olddir=`pwd`
cd $srcdir

echo -n "checking for gnulib-tool <http://www.gnu.org/software/gnulib/>... "
which gnulib-tool || {
	echo "*** No gnulib-tool found, please install it ***"
	exit 1
}

echo -n "checking for autoreconf <http://www.gnu.org/software/autoconf/>... "
which autoreconf || {
	echo "*** No autoreconf found, please install it ***"
	exit 1
}

echo "running gnulib-tool --update"
gnulib-tool --update || exit $?

echo "running autoreconf --install --verbose"
autoreconf --install --verbose || exit $?

cd $olddir
