// Copyright (C) 2012 Khaled Hosny and Barry Schwartz
//
// This file is part of LibUnicodeNames++.
// 
// LibUnicodeNames++ is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
// 
// LibUnicodeNames++ is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with LibUnicodeNames++.  If not, see
// <http://www.gnu.org/licenses/>.


#include <config.h>

#include <libunicodenames++.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libgen.h>

using namespace libunicodenames;

int
main (int argc, char *argv[])
{
  if (argc != 4)
    abort ();

  const char *locale = argv[1];

  unsigned int codepoint;
  sscanf (argv[2], "%x", &codepoint);

  const char *localedir = (argv[3][0] == '\0') ? NULL : argv[3];

  int exit_code = 1;
  const char *loc = setlocale (LC_MESSAGES, locale);
  if (loc == NULL)
    {
      exit_code = 77;		// The locale is unsupported. Skip the test.
    }
  else
    {
      printf ("|");
      printf ("%s|", loc);
      char *db_file = find_names_db (localedir);
      printf ("%s|", basename (db_file));
      unicodenames db (db_file);
      printf ("%s|", db.name (codepoint));
      delete db_file;
      exit_code = 0;
    }
  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
