// Copyright (C) 2012 Barry Schwartz
//
// This file is part of LibUnicodeNames.
// 
// LibUnicodeNames is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
// 
// LibUnicodeNames is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with LibUnicodeNames.  If not, see
// <http://www.gnu.org/licenses/>.


#if ! defined (__cplusplus)
#if ! defined (__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#error C99 or C++ is required.
#endif
#endif

#include "noinst_header.h"

#ifndef PKGDATADIR
#error You must define PKGDATADIR.
#endif

static const char pkgdatadir[] = PKGDATADIR;

char *
unicodenames_names_db_for_current_locale (void)
{
  const char *db_name = _("en.names-db");
  char *full_path =
    (char *) malloc (strlen (pkgdatadir) + strlen (db_name) + 1);
  strcpy (full_path, pkgdatadir);
  strcat (full_path, db_name);
  return full_path;
}


// local variables:
// c-file-style: "gnu"
// end:
