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

ACLOCAL_AMFLAGS = -I m4 -I m4_ax

SUBDIRS = lib . po tests

#--------------------------------------------------------------------------

NAMESLIST_EN = "http://www.unicode.org/Public/UNIDATA/NamesList.txt"
NAMESLIST_FR = "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt"

#--------------------------------------------------------------------------

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA = libunicodenames.pc

lib_LTLIBRARIES = libunicodenames.la
include_HEADERS = libunicodenames.h
dist_pkgdata_DATA = en.names-db fr.names-db en.blocks-db fr.blocks-db
info_TEXINFOS = libunicodenames.texi

AM_CPPFLAGS = 							\
	-DPKGDATADIR=\"${pkgdatadir}/\" 	\
	-DLOCALEDIR=\"${localedir}/\" 		\
	-DTEXTDOMAIN=\"${PACKAGE}\"

AM_CFLAGS = $(WARNING_CFLAGS) $(CFLAG_VISIBILITY)

libunicodenames_la_SOURCES = use_names_db.c use_blocks_db.c find_db.c	\
	common_code.c noinst_header.h libgettext.h
nodist_libunicodenames_la_SOURCES = config.h
libunicodenames_la_LDFLAGS = -no-undefined -version-info 1:2:0

#--------------------------------------------------------------------------

if CXX_FFI

AM_CXXFLAGS = $(WARNING_CXXFLAGS)

nodist_pkgconfig_DATA += libunicodenames++.pc

lib_LTLIBRARIES += libunicodenames++.la
include_HEADERS += libunicodenames++.h

libunicodenames___la_SOURCES = cxx_bindings.cxx noinst_header.h	\
	libgettext.h
nodist_libunicodenames___la_SOURCES = config.h
libunicodenames___la_LIBADD = libunicodenames.la
libunicodenames___la_LDFLAGS = -no-undefined -version-info 1:1:0

endif CXX_FFI

#--------------------------------------------------------------------------

if PYTHON_FFI

python_PYTHON = unicodenames.py
EXTRA_LTLIBRARIES = _unicodenames.la

_unicodenames_la_SOURCES = unicodenames_wrap.cxx
_unicodenames_la_CPPFLAGS = $(AX_SWIG_PYTHON_CPPFLAGS) $(AM_CPPFLAGS)
_unicodenames_la_CXXFLAGS = $(WARNING_CXXFLAGS) $(SWIG_PYTHON_WARNING_CXXFLAGS)
_unicodenames_la_LIBS = $(AX_SWIG_PYTHON_LIBS)
_unicodenames_la_LIBADD = libunicodenames++.la libunicodenames.la
_unicodenames_la_LDFLAGS = -module -shared -avoid-version -rpath '$(pyexecdir)'

# This ugly code exists so SWIG gets run if _either one_ of
# unicodenames.py and unicodenames_wrap.cxx is out of date or missing.
unicodenames.py unicodenames_wrap.cxx: stamp-pyffi
	@if test ! -f $@; then rm -f stamp-pyffi; else :; fi
	@if test ! -f $@; then $(MAKE) $(AM_MAKEFLAGS) stamp-pyffi; else :; fi

stamp-pyffi: unicodenames.i libunicodenames.h
	$(SWIG) -c++ $(AX_SWIG_PYTHON_OPT) -I$(srcdir) unicodenames.i
	@touch stamp-pyffi

# Install the Python extension after the C and C++ libraries, so it
# can be re-linked with them.
install-exec-hook: _unicodenames.la
	$(MKDIR_P) "$(DESTDIR)$(pyexecdir)" || exit 1
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install	\
		$(INSTALL) $(INSTALL_STRIP_FLAG) _unicodenames.la			\
		'$(DESTDIR)$(pyexecdir)'

uninstall-hook:
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall	\
		rm -f '$(DESTDIR)$(pyexecdir)/_unicodenames.la'

mostlyclean-local:
	$(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall	\
		rm -f _unicodenames.la

endif PYTHON_FFI

#--------------------------------------------------------------------------

EXTRA_DIST = $(srcdir)/po/Rules-doc m4/gnulib-cache.m4 .indent.pro

dist_noinst_SCRIPTS = make-names-db.awk make-blocks-db.awk
MAKE_NAMES_DB = LC_ALL=C $(GAWK) -f $(srcdir)/make-names-db.awk
MAKE_BLOCKS_DB = LC_ALL=C $(GAWK) -f $(srcdir)/make-blocks-db.awk

nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt
nodist_EXTRA_DATA += NamesList.UTF-8 ListeDesNoms.UTF-8

rebuild-db: rebuild-names-db rebuild-blocks-db

rebuild-names-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_NAMES_DB) NamesList.UTF-8 > $(srcdir)/en.names-db
	$(MAKE_NAMES_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.names-db

rebuild-blocks-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_BLOCKS_DB) NamesList.UTF-8 > $(srcdir)/en.blocks-db
	$(MAKE_BLOCKS_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.blocks-db

CRLF_TO_LF = $(SED) -e 's/\r//g'

NamesList.UTF-8:
	$(WGET) $(NAMESLIST_EN) -O $@

ListeDesNoms.UTF-8:
	$(WGET) $(NAMESLIST_FR) -O $@

#--------------------------------------------------------------------------

######################################################################
##                                                                  ##
##  A note for the developers:                                      ##
##                                                                  ##
##  You should use Mercurial (not Git) when making a dist package.  ##
##  Otherwise you will not get the proper ChangeLog file.           ##
##                                                                  ##
######################################################################

dist-hook: make-changelog

make-changelog:
	@if hg log -r tip > /dev/null 2> /dev/null; then \
		hg log --style=changelog > $(distdir)/ChangeLog; \
		echo; \
		echo "----------------------------------------------------------------"; \
		echo "hg log --style=changelog > $(distdir)/ChangeLog"; \
		echo "----------------------------------------------------------------"; \
		echo; \
	else \
		echo "If you do not mind, please report that the ChangeLog is missing." > $(distdir)/ChangeLog; \
		echo "Report at: https://github.com/chemoelectric/libunicodenames/issues" >> $(distdir)/ChangeLog; \
		echo; \
		echo "----------------------------------------------------------------"; \
		echo "The ChangeLog was not made! You need Mercurial to make it."; \
		echo "If you are making a real release, please do it from within"; \
		echo "a Mercurial repository. Consider using Mercurial with hg-git."; \
		echo "----------------------------------------------------------------"; \
		echo; \
	fi

MOSTLYCLEANFILES = unicodenames.py unicodenames.pyc
MOSTLYCLEANFILES += unicodenames.pyo unicodenames_wrap.cxx
MOSTLYCLEANFILES += stamp-pyffi

DISTCLEANFILES = NamesList.txt ListeDesNoms.txt
DISTCLEANFILES += NamesList.UTF-8 ListeDesNoms.UTF-8

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
