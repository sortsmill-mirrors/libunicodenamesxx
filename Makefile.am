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

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = intl . po
if TESTSUITE
SUBDIRS += tests
endif TESTSUITE

#--------------------------------------------------------------------------

NAMESLIST_EN = "http://www.unicode.org/Public/UNIDATA/NamesList.txt"
NAMESLIST_EN_ENCODING = ISO-8859-1
NAMESLIST_FR = "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt"
NAMESLIST_FR_ENCODING = UTF-8

#--------------------------------------------------------------------------

pkgconfigdir = ${libdir}/pkgconfig
nodist_pkgconfig_DATA = libunicodenames.pc libunicodenames++.pc

lib_LTLIBRARIES = libunicodenames.la libunicodenames++.la
include_HEADERS = libunicodenames.h
dist_pkgdata_DATA = en.names-db fr.names-db

EXTRA_SCRIPTS = make-names-db.awk

MAKE_NAMES_DB = $(ENV) LC_ALL=C $(GAWK) -f $(srcdir)/make-names-db.awk

AM_CPPFLAGS = -DPKGDATADIR=\"${pkgdatadir}/\"
AM_CFLAGS = $(WARNING_CFLAGS)
AM_CXXFLAGS = $(WARNING_CXXFLAGS)

libunicodenames_la_SOURCES = use_names_db.c find_names_db.c
libunicodenames_la_SOURCES += libunicodenames.h noinst_header.h
libunicodenames_la_SOURCES += libgettext.h
nodist_libunicodenames_la_SOURCES = config.h
libunicodenames_la_LDFLAGS = -no-undefined -version-info 1:0:0

libunicodenames___la_SOURCES = cxx_bindings.cxx
libunicodenames___la_SOURCES += libunicodenames.h noinst_header.h
libunicodenames___la_SOURCES += libgettext.h
nodist_libunicodenames___la_SOURCES = $(nodist_libunicodenames_la_SOURCES)
libunicodenames___la_LIBADD = libunicodenames.la
libunicodenames___la_LDFLAGS = $(libunicodenames_la_LDFLAGS)

nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt
nodist_EXTRA_DATA += NamesList.UTF-8 ListeDesNoms.UTF-8

rebuild-names-db: NamesList.UTF-8 ListeDesNoms.UTF-8
	$(MAKE_NAMES_DB) NamesList.UTF-8 > $(srcdir)/en.names-db
	$(MAKE_NAMES_DB) ListeDesNoms.UTF-8 > $(srcdir)/fr.names-db

CRLF_TO_LF = $(SED) -e 's/\r//g'

NamesList.UTF-8: NamesList.txt
	$(ICONV) -f $(NAMESLIST_EN_ENCODING) NamesList.txt -t UTF-8 | $(CRLF_TO_LF) > NamesList.UTF-8

ListeDesNoms.UTF-8: ListeDesNoms.txt
	$(ICONV) -f $(NAMESLIST_FR_ENCODING) ListeDesNoms.txt -t UTF-8 | $(CRLF_TO_LF) > ListeDesNoms.UTF-8

NamesList.txt:
	$(WGET) $(NAMESLIST_EN) -O $@

ListeDesNoms.txt:
	$(WGET) $(NAMESLIST_FR) -O $@

#--------------------------------------------------------------------------

if PYTHON_FFI

python_PYTHON = unicodenames.py
python_LTLIBRARIES = _unicodenames.la

_unicodenames_la_SOURCES = unicodenames_wrap.cxx libunicodenames.h
_unicodenames_la_CPPFLAGS = $(AX_SWIG_PYTHON_CPPFLAGS)
_unicodenames_la_CXXFLAGS = $(WARNING_CXXFLAGS) $(SWIG_PYTHON_WARNING_CXXFLAGS)
_unicodenames_la_LIBS = $(AX_SWIG_PYTHON_LIBS)
_unicodenames_la_LIBADD = libunicodenames++.la libunicodenames.la
_unicodenames_la_LDFLAGS = -module -shared -avoid-version

# This ugly code exists so SWIG gets run if _either one_ of
# unicodenames.py and unicodenames_wrap.cxx is out of date or missing.
unicodenames.py unicodenames_wrap.cxx: stamp-pyffi
	@if test ! -f $@; then rm -f stamp-pyffi; else :; fi
	@if test ! -f $@; then $(MAKE) $(AM_MAKEFLAGS) stamp-pyffi; else :; fi

stamp-pyffi: unicodenames.i libunicodenames.h
	$(SWIG) -c++ $(AX_SWIG_PYTHON_OPT) -I$(srcdir) unicodenames.i
	@touch stamp-pyffi

endif PYTHON_FFI

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
