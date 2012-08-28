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

//-------------------------------------------------------------------
// FIXME: Include a test that the patches are complete -- that they
// cover the entire annotation.
//
// FIXME: Include a test that the patches do not overflow -- that they
// cover only the annotation and nothing past it.


#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *
make_patch (unicodenames & db, unsigned int codepoint)
{
  char *patch = NULL;
  const char *name = db.name (codepoint);
  const char *annot = db.annotation (codepoint);
  if (name != NULL && annot != NULL)
    {
      patch = (char *) malloc (strlen (name) + strlen (annot) + 100);
      (void) sprintf (patch, "%04X\t%s\n%s", codepoint, name, annot);
    }
  return patch;
}

int
main (int argc, char *argv[])
{
  int exit_code = 1;

  const char *db_file = argv[1];
  const char *nameslist_file = argv[2];
  //unsigned int random_codepoint_count;
  //(void) sscanf(argv[3], "%u", &random_codepoint_count);

  unicodenames db (db_file);

  char nameslist[2000000];
  memset (nameslist, 0, sizeof nameslist);
  FILE *f = fopen (nameslist_file, "rb");
  (void) fread (nameslist, 1, sizeof nameslist, f);
  fclose (f);

  int failure_count = 0;

  // Test the codepoints up to 0x10FFFF.
  for (int codepoint = 0; codepoint <= 0x10FFFF; codepoint++)
    {
      char *patch = make_patch (db, codepoint);
      if (patch != NULL)
        {
          if (strstr (nameslist, patch) == NULL)
            {
              (void) printf ("Failure: codepoint = %X\n", codepoint);
              failure_count++;
            }
          free (patch);
        }
    }

  if (failure_count == 0)
    exit_code = 0;

  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
