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

ACLOCAL_AMFLAGS = -I m4 --install

SUBDIRS = lib . po tests

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA =

dist_pkgdata_DATA =
nodist_pkgdata_DATA =
lib_LTLIBRARIES =
include_HEADERS =
nodist_bin_SCRIPTS =
dist_noinst_SCRIPTS =
nodist_pkglibexec_SCRIPTS =
nodist_EXTRA_DATA =
dist_man_MANS =
nodist_man_MANS =
EXTRA_DIST =
MOSTLYCLEANFILES =
CLEANFILES =
DISTCLEANFILES = Makefile GNUmakefile

AM_CXXFLAGS = $(WARNING_CXXFLAGS)
AM_CPPFLAGS = 											\
	-I$(top_builddir)/lib -I$(top_srcdir)/lib			\
	-DPKGDATADIR=\"${pkgdatadir}/\"	 					\
	-DLOCALEDIR=\"${localedir}/\" 						\
	-DTEXTDOMAIN=\"${PACKAGE}\"
AM_LDFLAGS = -version-info 1:2:0 $(LIBUNICODENAMES_LIBS)

EXTRA_DIST += examples/print_names.cxx examples/print_blocks.cxx

#--------------------------------------------------------------------------

nodist_pkgconfig_DATA += libunicodenames++.pc

lib_LTLIBRARIES += libunicodenames++.la
include_HEADERS += libunicodenames++.h

libunicodenames___la_SOURCES = cxx_bindings.cxx noinst_header.h	\
	libgettext.h
nodist_libunicodenames___la_SOURCES = config.h
libunicodenames___la_CFLAGS = $(LIBUNICODENAMES_CFLAGS)
libunicodenames___la_LIBADD = lib/libgnu.la

dist_man_MANS = doc/libunicodenames++.3 doc/libunicodenames++.h.3

#--------------------------------------------------------------------------

EXTRA_DIST += $(srcdir)/po/Rules-doc m4/gnulib-cache.m4 .indent.pro

#--------------------------------------------------------------------------

distclean-local:
	if test '$(top_srcdir)' -ef '$(top_builddir)'; then		\
		:; 													\
	else													\
		for dir in . tests; do								\
             rm -f "$(top_builddir)/$${dir}/.indent.pro";	\
		done;												\
	fi

#--------------------------------------------------------------------------
#
# Automatic ChangeLog generation at `make dist', if one has
# sortsmill-changelogger.

dist-hook: dist-changelog
@dist_changelog_rules@

#--------------------------------------------------------------------------

include indent.am

blacklist_for_indent += config.h libgettext.h

@ifGNUmake@indent: indent-recursive
@ifGNUmake@	$(call do_indent, $(libunicodenames___la_SOURCES))
@ifGNUmake@	$(call do_indent, $(include_HEADERS))
@ifGNUmake@
@ifGNUmake@indent-recursive:
@ifGNUmake@	$(MAKE) -C tests $(AM_MAKEFLAGS) indent

#--------------------------------------------------------------------------
