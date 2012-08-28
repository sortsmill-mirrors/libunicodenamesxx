#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#  Copyright (C) 2012 Barry Schwartz
# 
#  This file is part of LibUnicodeNames.
#  
#  LibUnicodeNames is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation, either version 3 of
#  the License, or (at your option) any later version.
#  
#  LibUnicodeNames is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with LibUnicodeNames.  If not, see
#  <http://www.gnu.org/licenses/>.


AC_PREREQ([2.69])
AC_INIT([libunicodenames],[1.0.0-beta1],[https://github.com/chemoelectric/libunicodenames/issues])
AC_CONFIG_SRCDIR([libunicodenames.c])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_TESTDIR([tests])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.12.2 silent-rules -Wall -Werror])
AM_MAINTAINER_MODE([enable])
AC_USE_SYSTEM_EXTENSIONS
AM_PROG_AR
LT_INIT

AC_ARG_ENABLE([tests],
   [AS_HELP_STRING([--disable-tests],[do not build the test suite])],
   [],[enable_tests=yes])
AM_CONDITIONAL([TESTSUITE],[test x"${enable_tests}" = xyes])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC_C99
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_SED
AC_PATH_PROGS([ENV],[env],[env])
AC_PATH_PROGS([GAWK],[gawk],[gawk])
AC_PATH_PROGS([ICONV],[iconv],[iconv])
AC_PATH_PROGS([WGET],[wget],[wget])

AC_ARG_ENABLE([python],
   [AS_HELP_STRING([--enable-python],[build Python bindings (requires SWIG >= 2.0.4)])],
   [
      AM_PATH_PYTHON
      AX_PKG_SWIG([2.0.4],[],[AC_MSG_ERROR([SWIG is required to build the Python bindings.])])
      AX_SWIG_PYTHON
   ])
AM_CONDITIONAL([PYTHON_FFI],[test x"${enable_python}" = xyes])
AC_SUBST([enable_python])


# Checks for libraries.


# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])
AC_HEADER_STDBOOL


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

AC_SUBST([WARNING_CFLAGS],[])
AC_SUBST([EXTRA_WARNING_CFLAGS],[])
AC_SUBST([SWIG_PYTHON_WARNING_CFLAGS],[])
AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CFLAGS+=" -Wall"])
AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CFLAGS+=" -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wno-unused-but-set-variable],
                      [SWIG_PYTHON_WARNING_CFLAGS+=" -Wno-unused-but-set-variable"])


# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor memset strstr])


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libunicodenames.pc])
AC_CONFIG_FILES([unicodenames.i])
AC_CONFIG_FILES([tests/Makefile tests/atlocal])
AC_OUTPUT
