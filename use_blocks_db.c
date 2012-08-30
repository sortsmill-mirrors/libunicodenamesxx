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

typedef struct unicodenames_blocks___record
{
  unsigned int start_point;
  unsigned int end_point;
  unsigned int string_offset;
} unicodenames_blocks___record;

typedef struct unicodenames_blocks___db
{
  unsigned int version;
  unsigned int block_count;
  unicodenames_blocks___record *records;
  char *strings;
} unicodenames_blocks___db;

static const char *blocks_db_id_string = "libunicodenames blocks db      ";

static bool
read_records (FILE * f, unicodenames_blocks___record **records, unsigned int size)
{
  *records = (unicodenames_blocks___record *) malloc (size * sizeof (unicodenames_blocks___record));
  bool successful = (*records != NULL);
  size_t j = 0;
  while (successful && j < size)
    {
      successful = __read_uint (f, &((*records)[j].start_point));
      if (successful)
        successful = __read_uint (f, &((*records)[j].end_point));
      if (successful)
        successful = __read_uint (f, &((*records)[j].string_offset));
      j++;
    }
  if (!successful)
    {
      free (*records);
      *records = NULL;
    }
  return successful;
}

static bool
read_blocks_db_tables (FILE * f, unicodenames_blocks_db handle)
{
  unsigned int strings_size;

  bool successful = (__read_uint (f, &handle->version) && handle->version == 1);
  if (successful)
    successful = __read_uint (f, &handle->block_count);
  if (successful)
    successful = read_records (f, &handle->records, handle->block_count);
  if (successful)
    successful = __read_uint (f, &strings_size);
  if (successful)
    successful = __read_strings (f, &handle->strings, strings_size);
  return successful;
}

unicodenames_blocks_db
unicodenames_blocks_db_open (const char *filename)
{
  unicodenames_blocks_db handle = NULL;

  FILE *f = fopen (filename, "rb");
  if (f != NULL)
    {
      if (__string_matches (f, blocks_db_id_string))
        {
          handle =
            (unicodenames_blocks_db) malloc (sizeof (unicodenames_blocks___db));
          if (handle != NULL)
            {
              handle->records = NULL;
              handle->strings = NULL;
              bool successful = read_blocks_db_tables (f, handle);
              if (!successful)
                {
                  unicodenames_blocks_db_close (handle);
                  handle = NULL;
                }
            }
        }
      fclose (f);
    }

  return handle;
}

void
unicodenames_blocks_db_close (unicodenames_blocks_db handle)
{
  free (handle->records);
  free (handle->strings);
  free (handle);
}


// local variables:
// c-file-style: "gnu"
// end:
