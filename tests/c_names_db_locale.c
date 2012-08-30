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


#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libgen.h>

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
  printf("%s\n", loc);
  char *db_file = uninm_names_db_for_current_locale (localedir);
  printf("%s\n", basename(db_file));
  uninm_names_db db = uninm_names_db_open (db_file);
  if (db != NULL)
    {
      exit_code = 0;
      printf ("%s\n", uninm_name (db, codepoint));
      uninm_names_db_close (db);
    }
  free (db_file);
  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
