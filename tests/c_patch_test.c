// Copyright (C) 2012 Khaled Hosny and Barry Schwartz
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


#include <config.h>

#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// UTF-8 encodings.
static const char bullet[] = "\xe2\x80\xa2";
static const char arrow[] = "\xe2\x86\x92";
static const char equiv[] = "\xe2\x89\x8d";
static const char approx[] = "\xe2\x89\x85";

static char *
make_patch (uninm_names_db db, unsigned int codepoint)
{
  size_t bullet_len = strlen (bullet);
  size_t arrow_len = strlen (arrow);
  size_t equiv_len = strlen (equiv);
  size_t approx_len = strlen (approx);

  char *patch = NULL;
  const char *name = uninm_name (db, codepoint);
  const char *annot = uninm_annotation (db, codepoint);
  if (name != NULL && annot != NULL)
    {
      size_t patch_len = strlen (name) + strlen (annot) + 100;
      patch = (char *) malloc (patch_len);
      memset (patch, 0, patch_len);
      (void) sprintf (patch, "%04X\t%s\n", codepoint, name);
      int i = 0;
      int j = strchr (patch, '\0') - patch;
      while (annot[i] != '\0')
	{
	  if (strncmp (annot + i, bullet, bullet_len) == 0)
	    {
	      patch[j] = '*';
	      i += bullet_len;
	    }
	  else if (strncmp (annot + i, arrow, arrow_len) == 0)
	    {
	      patch[j] = 'x';
	      i += arrow_len;
	    }
	  else if (strncmp (annot + i, equiv, equiv_len) == 0)
	    {
	      patch[j] = ':';
	      i += equiv_len;
	    }
	  else if (strncmp (annot + i, approx, approx_len) == 0)
	    {
	      patch[j] = '#';
	      i += approx_len;
	    }
	  else
	    {
	      patch[j] = annot[i];
	      i++;
	    }
	  j++;
	}
    }
  return patch;
}

int
main (int argc, char *argv[])
{
  if (argc != 3)
    abort ();

  setlocale (LC_ALL, "C");

  int exit_code = 1;

  const char *db_file = argv[1];
  const char *nameslist_file = argv[2];

  uninm_names_db db = uninm_names_db_open (db_file);
  if (db != NULL)
    {
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

      uninm_names_db_close (db);
    }

  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
