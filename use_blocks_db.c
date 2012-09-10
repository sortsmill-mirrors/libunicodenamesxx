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
# if ! defined (__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#  error C99 or C++ is required.
# endif
#endif

#include "noinst_header.h"

typedef struct uninm_blocks___db
{
  unsigned int version;
  unsigned int block_count;
  unsigned int *start_points;
  unsigned int *end_points;
  unsigned int *string_offsets;
  char *strings;
} uninm_blocks___db;

static const char *blocks_db_id_string = "libunicodenames blocks db      ";

static bool
read_blocks_db_tables (FILE *f, uninm_blocks_db handle)
{
  unsigned int strings_size;

  bool successful = (__read_uint (f, &handle->version)
		     && handle->version == 1);
  if (successful)
    successful = __read_uint (f, &handle->block_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->start_points, handle->block_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->end_points, handle->block_count);
  if (successful)
    successful =
      __read_uint_array (f, &handle->string_offsets, handle->block_count);
  if (successful)
    successful = __read_uint (f, &strings_size);
  if (successful)
    successful = __read_strings (f, &handle->strings, strings_size);
  return successful;
}

uninm_blocks_db
uninm_blocks_db_open (const char *filename)
{
  uninm_blocks_db handle = NULL;

  FILE *f = fopen (filename, "rb");
  if (f != NULL)
    {
      if (__string_matches (f, blocks_db_id_string))
	{
	  handle = (uninm_blocks_db) malloc (sizeof (uninm_blocks___db));
	  if (handle != NULL)
	    {
	      handle->start_points = NULL;
	      handle->end_points = NULL;
	      handle->string_offsets = NULL;
	      handle->strings = NULL;
	      bool successful = read_blocks_db_tables (f, handle);
	      if (!successful)
		{
		  uninm_blocks_db_close (handle);
		  handle = NULL;
		}
	    }
	}
      fclose (f);
    }

  return handle;
}

void
uninm_blocks_db_close (uninm_blocks_db handle)
{
  free (handle->start_points);
  free (handle->end_points);
  free (handle->string_offsets);
  free (handle->strings);
  free (handle);
}

size_t
uninm_num_blocks (uninm_blocks_db handle)
{
  return handle->block_count;
}

static inline bool
in_range (uninm_blocks_db handle, int i)
{
  return (0 <= i && (size_t) i < handle->block_count);
}

unsigned int
uninm_block_start (uninm_blocks_db handle, int i)
{
  return in_range (handle, i) ? handle->start_points[i] : 0xffffffff;
}

unsigned int
uninm_block_end (uninm_blocks_db handle, int i)
{
  return in_range (handle, i) ? handle->end_points[i] : 0xffffffff;
}

const char *
uninm_block_name (uninm_blocks_db handle, int i)
{
  return in_range (handle, i) ? (handle->strings +
				 handle->string_offsets[i]) : NULL;
}
