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
AC_INIT([libunicodenamespp],[1.1.0],[https://github.com/sortsmill/libunicodenames++/issues])
AC_CONFIG_SRCDIR([libunicodenames++.pc.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_TESTDIR([tests])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.12.2 dist-xz -Wall -Wno-portability])
AC_USE_SYSTEM_EXTENSIONS
m4_ifdef([AM_PROG_AR],[AM_PROG_AR])
LT_INIT
AM_GNU_GETTEXT_VERSION([0.18.1])

# I am going to try enabling silent-rules by default, so builders are
# more likely to see warnings. Use --disable-silent-rules or "make
# V=1" if you need to see the rules.
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

VERSION_MAJOR=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_MINOR=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_PATCH=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
VERSION_EXTRA=`AS_ECHO(["${PACKAGE_VERSION}"]) | sed -e 's/^[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\(.*\)/\1/' \
                                                     -e 's/^_//'`
VERSION_EXTRA_SHORT=`AS_ECHO(["${VERSION_EXTRA}"]) | sed -e 's/alpha/a/' -e 's/beta/b/'`
AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_PATCH])
AC_SUBST([VERSION_EXTRA])
AC_SUBST([VERSION_EXTRA_SHORT])

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
AC_PATH_PROGS([INDENT],[indent],[indent])
AC_PATH_PROGS([WGET],[wget],[wget])

#--------------------------------------------------------------------------
#
# Checks for libraries.

PKG_CHECK_MODULES([LIBUNICODENAMES],[libunicodenames])
PKG_CHECK_VAR([LIBUNICODENAMES_DATAROOTDIR],[libunicodenames],[datarootdir])

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

#AC_SUBST([WARNING_CFLAGS],[])
#if test x"${GCC}" = xyes; then
#   AC_LANG_PUSH([C])
#   AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CFLAGS+=" -Wall"])
#   AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CFLAGS+=" -Wextra"])
#   AX_CHECK_COMPILE_FLAG([-Wcast-align],[WARNING_CFLAGS+=" -Wcast-align"])
#   AX_CHECK_COMPILE_FLAG([-Wbad-function-cast],[WARNING_CFLAGS+=" -Wbad-function-cast"])
#   AX_CHECK_COMPILE_FLAG([-Wc++-compat],[WARNING_CFLAGS+=" -Wc++-compat"])
#   AX_CHECK_COMPILE_FLAG([-Wno-unused-result],[WARNING_CFLAGS+=" -Wno-unused-result"])
#   AC_LANG_POP
#fi

AC_SUBST([WARNING_CXXFLAGS],[])
if test x"${GXX}" = xyes; then
   AC_LANG_PUSH([C++])
   AX_CHECK_COMPILE_FLAG([-Wall],[WARNING_CXXFLAGS+=" -Wall"])
   AX_CHECK_COMPILE_FLAG([-Wextra],[WARNING_CXXFLAGS+=" -Wextra"])
   AX_CHECK_COMPILE_FLAG([-Wcast-align],[WARNING_CXXFLAGS+=" -Wcast-align"])
   AX_CHECK_COMPILE_FLAG([-Wno-unused-result],[WARNING_CXXFLAGS+=" -Wno-unused-result"])
   AC_LANG_POP
fi

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

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libunicodenames++.pc])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([tests/Makefile tests/atlocal])

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
