#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#  Copyright (C) 2012, 2013 Khaled Hosny and Barry Schwartz
# 
#  This file is part of LibUnicodeNames++.
#  
#  LibUnicodeNames++ is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation, either version 3 of
#  the License, or (at your option) any later version.
#  
#  LibUnicodeNames++ is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#  
#  You should have received a copy of the GNU Lesser General Public
#  License along with LibUnicodeNames++.  If not, see
#  <http://www.gnu.org/licenses/>.

#--------------------------------------------------------------------------

AC_PREREQ([2.68])
AC_INIT([LibUnicodeNames++],
        [1.2.0_beta1],
        [http://bitbucket.org/sortsmill/libunicodenamesxx/issues],
        [libunicodenamesxx],
        [http://bitbucket.org/sortsmill/libunicodenamesxx])

AC_CONFIG_SRCDIR([libunicodenames++.pc.in])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CANONICAL_BUILD                 dnl On what platform are we compiling?
AC_CANONICAL_HOST                  dnl For what platform are we compiling?
AC_USE_SYSTEM_EXTENSIONS           dnl Define such macros as _GNU_SOURCE.
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11 dist-xz -Wall -Wno-portability])
AM_SILENT_RULES([yes])
AX_CHECK_GNU_MAKE
m4_ifdef([AM_PROG_AR],[AM_PROG_AR])
LT_INIT
AM_GNU_GETTEXT_VERSION([0.18.1])

AC_CONFIG_TESTDIR([tests])

StM_ANALYZE_PACKAGE_VERSION

#--------------------------------------------------------------------------
#
# Checks for programs.

AC_PROG_CC
AC_PROG_CC_C99
gl_EARLY
gl_INIT
AM_PROG_CC_C_O
AC_PROG_CXX
AC_PROG_CXX_C_O
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_YACC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P
AC_PROG_SED
StM_PROG_GNU_INDENT

test -z "${GNU_INDENT}" && GNU_INDENT=/bin/false

#--------------------------------------------------------------------------
#
# Checks for libraries.

PKG_CHECK_MODULES([LIBUNICODENAMES],[libunicodenames])
AC_ARG_VAR([LIBUNICODENAMES_PKGDATADIR],
           [directory where libunicodenames installed its shared data])
# PKG_CHECK_VAR requires pkg-config >= 0.28
m4_ifdef([PKG_CHECK_VAR],
   [PKG_CHECK_VAR([LIBUNICODENAMES_PKGDATADIR],[libunicodenames],[pkgdatadir])],
   [AC_SUBST([LIBUNICODENAMES_PKGDATADIR],['@S|@{pkgdatadir}'])])

#--------------------------------------------------------------------------
#
# Checks for header files.

AC_CHECK_HEADERS([argz.h fcntl.h float.h inttypes.h langinfo.h libintl.h limits.h locale.h malloc.h stddef.h stdint.h stdio_ext.h stdlib.h string.h sys/param.h unistd.h wchar.h])
AC_HEADER_STDBOOL
AC_FUNC_ALLOCA

#--------------------------------------------------------------------------
#
# Checks for typedefs, structures, and compiler characteristics.

AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

AC_SUBST([WARNING_CXXFLAGS],[])
StM_GNU_CXX_FLAGS([WARNING_CXXFLAGS],
   [-Wall -Wextra -Wcast-align -Wno-unused-result],
   [-Wl,--warn-common])

#--------------------------------------------------------------------------
#
# Checks for library functions.

AC_FUNC_MALLOC
AM_GNU_GETTEXT([external])
AC_FUNC_MBRTOWC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([__argz_count __argz_next __argz_stringify floor getcwd localeconv mblen mbrlen memchr mempcpy memset munmap nl_langinfo setlocale stpcpy strcasecmp strchr strcspn strdup strstr strtoul])

#--------------------------------------------------------------------------

AC_SUBST([LT_OBJDIR],["${lt_cv_objdir}"])

StM_CHANGELOGGERIZE

StM_CONFIG_MAKEFILES
StM_CONFIG_MAKEFILES([tests/Makefile],[tests/GNUmakefile])

AC_CONFIG_FILES([libunicodenames++.pc])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([tests/atlocal])

AC_CONFIG_COMMANDS([doc],[AS_MKDIR_P([doc])])

AC_CONFIG_COMMANDS([.indent.pro],
   [
      if test "${ac_srcdir}" -ef "${ac_builddir}"; then
         :
      else
         for dir in . tests; do
             rm -f "${ac_builddir}/${dir}/.indent.pro"
             (cd "${ac_builddir}/${dir}" && ${LN_S} "${ac_srcdir}"/.indent.pro .indent.pro)
         done
      fi
   ])

AC_OUTPUT

#--------------------------------------------------------------------------
