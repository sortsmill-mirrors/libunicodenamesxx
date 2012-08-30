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

typedef struct uninm_names___db
{
  unsigned int version;
  unsigned int codepoint_count;
  unsigned int *codepoints;
  unsigned int *name_offsets;
  unsigned int *annot_offsets;
  char *strings;
} uninm_names___db;

static const char *names_db_id_string = "libunicodenames names db       ";

static bool
read_names_db_tables (FILE * f, uninm_names_db handle)
{
  unsigned int strings_size;

  bool successful = (__read_uint (f, &handle->version) && handle->version == 1);
  if (successful)
    successful = __read_uint (f, &handle->codepoint_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->codepoints, handle->codepoint_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->name_offsets, handle->codepoint_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->annot_offsets, handle->codepoint_count);
  if (successful)
    successful = __read_uint (f, &strings_size);
  if (successful)
    successful = __read_strings (f, &handle->strings, strings_size);
  return successful;
}

uninm_names_db
uninm_names_db_open (const char *filename)
{
  uninm_names_db handle = NULL;

  FILE *f = fopen (filename, "rb");
  if (f != NULL)
    {
      if (__string_matches (f, names_db_id_string))
        {
          handle =
            (uninm_names_db) malloc (sizeof (uninm_names___db));
          if (handle != NULL)
            {
              handle->codepoints = NULL;
              handle->name_offsets = NULL;
              handle->annot_offsets = NULL;
              handle->strings = NULL;
              bool successful = read_names_db_tables (f, handle);
              if (!successful)
                {
                  uninm_names_db_close (handle);
                  handle = NULL;
                }
            }
        }
      fclose (f);
    }

  return handle;
}

void
uninm_names_db_close (uninm_names_db handle)
{
  free (handle->codepoints);
  free (handle->name_offsets);
  free (handle->annot_offsets);
  free (handle->strings);
  free (handle);
}

static int
compare_codepoints (const void *codepoint1, const void *codepoint2)
{
  const unsigned int *cp1 = (const unsigned int *) codepoint1;
  const unsigned int *cp2 = (const unsigned int *) codepoint2;
  return ((*cp1 < *cp2) ? -1 : ((*cp1 == *cp2) ? 0 : 1));
}

static int
codepoint_index (uninm_names_db handle, unsigned int codepoint)
{
  int index = -1;
  unsigned int *p = (unsigned int *) bsearch (&codepoint, handle->codepoints,
                                              handle->codepoint_count,
                                              sizeof (unsigned int),
                                              compare_codepoints);
  if (p != NULL)
    index = p - handle->codepoints;
  return index;
}

static inline unsigned int
name_offset_at_index (uninm_names_db handle, int index)
{
  return handle->name_offsets[index];
}

static inline unsigned int
annot_offset_at_index (uninm_names_db handle, int index)
{
  return handle->annot_offsets[index];
}

static inline const char *
name_at_index (uninm_names_db handle, int index)
{
  return (const char *) (handle->strings +
                         name_offset_at_index (handle, index));
}

static inline const char *
annot_at_index (uninm_names_db handle, int index)
{
  return (const char *) (handle->strings +
                         annot_offset_at_index (handle, index));
}

const char *
uninm_name (uninm_names_db handle, unsigned int codepoint)
{
  const char *name = NULL;
  int index = codepoint_index (handle, codepoint);
  if (0 <= index)
    name = name_at_index (handle, index);
  return name;
}

const char *
uninm_annotation (uninm_names_db handle, unsigned int codepoint)
{
  const char *annot = NULL;
  int index = codepoint_index (handle, codepoint);
  if (0 <= index)
    annot = annot_at_index (handle, index);
  return annot;
}

// local variables:
// c-file-style: "gnu"
// end:
