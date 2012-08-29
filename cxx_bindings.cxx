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

#include "noinst_header.h"

using namespace libunicodenames;

const char *
unicodenames_exception::what ()
throw ()
{
  return "unknown exception";
}

const char *
memory_exhausted::what ()
throw ()
{
  return ("virtual memory exhausted");
}

const char *
open_failed::what ()
throw ()
{
  return ("open failed");
}

char *
libunicodenames::names_db_for_current_locale ()
{
  char *c_path = unicodenames_names_db_for_current_locale ();
  if (!c_path)
    throw memory_exhausted ();
  char *path = new char[strlen (c_path) + 1];
  if (!path)
    throw memory_exhausted ();
  strcpy (path, c_path);
  free (c_path);
  return path;
}

unicodenames::unicodenames (const char *filename)
{
  db = unicodenames_names_db_open (filename);
  if (!db)
    throw open_failed ();
}

unicodenames::~unicodenames ()
{
  unicodenames_names_db_close (db);
}

// local variables:
// c-file-style: "gnu"
// end:
