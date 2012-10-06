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

#include <config.h>

#include "noinst_header.h"

using namespace libunicodenames;

const char *
unicodenames_exception::what ()
throw ()
{
  return _("unknown exception");
}

const char *
memory_exhausted::what ()
throw ()
{
  return (_("virtual memory exhausted"));
}

const char *
open_failed::what ()
throw ()
{
  return (_("open failed"));
}

const char *
index_error::what ()
throw ()
{
  return (_("index error"));
}

static char *
malloc_to_new (const char *s)
{
  char *t = new char[strlen (s) + 1];
  if (!t)
    throw memory_exhausted ();
  strcpy (t, s);
  return t;
}

char *
libunicodenames::find_names_db (const char *locale_base)
{
  char *c_path = uninm_find_names_db (locale_base);
  if (!c_path)
    throw memory_exhausted ();
  char *path = malloc_to_new (c_path);
  free (c_path);
  return path;
}

char *
libunicodenames::find_blocks_db (const char *locale_base)
{
  char *c_path = uninm_find_blocks_db (locale_base);
  if (!c_path)
    throw memory_exhausted ();
  char *path = malloc_to_new (c_path);
  free (c_path);
  return path;
}

unicodenames::unicodenames (const char *filename)
{
  db = uninm_names_db_open (filename);
  if (!db)
    throw open_failed ();
}

unicodenames::~unicodenames ()
{
  uninm_names_db_close (db);
}

unicodeblocks::unicodeblocks (const char *filename)
{
  db = uninm_blocks_db_open (filename);
  if (!db)
    throw open_failed ();
}

unicodeblocks::~unicodeblocks ()
{
  uninm_blocks_db_close (db);
}

unsigned int
unicodeblocks::block_start (int i)
{
  check_index (i);
  return uninm_block_start (db, i);
}

unsigned int
unicodeblocks::block_end (int i)
{
  check_index (i);
  return uninm_block_end (db, i);
}

const char *
unicodeblocks::name (int i)
{
  check_index (i);
  return uninm_block_name (db, i);
}

// local variables:
// c-file-style: "gnu"
// end:
