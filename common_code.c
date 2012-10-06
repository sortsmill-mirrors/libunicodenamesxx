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

#if ! defined (__cplusplus)
#if ! defined (__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#error C99 or C++ is required.
#endif
#endif

#include "noinst_header.h"

bool
__string_matches (FILE *f, const char *s)
{
  const size_t s_len = strlen (s);
  char buffer[s_len + 1];
  size_t num_bytes = fread (buffer, 1, s_len + 1, f);
  return (num_bytes == s_len + 1 && memcmp (buffer, s, s_len + 1) == 0);
}

bool
__read_uint (FILE *f, unsigned int *i)
{
  unsigned char buffer[4];
  size_t num_bytes = fread (buffer, 1, 4, f);
  if (num_bytes == 4)
    *i =
      (unsigned int) buffer[0] | ((unsigned int) buffer[1] << 8) |
      ((unsigned int) buffer[2] << 16) | ((unsigned int) buffer[3] << 24);
  return (num_bytes == 4);
}

bool
__read_uint_array (FILE *f, unsigned int **i_array, size_t size)
{
  *i_array = (unsigned int *) malloc (size * sizeof (unsigned int));
  bool successful = (*i_array != NULL);
  size_t j = 0;
  while (successful && j < size)
    {
      successful = __read_uint (f, &(*i_array)[j]);
      j++;
    }
  if (!successful)
    {
      free (*i_array);
      *i_array = NULL;
    }
  return successful;
}

bool
__read_strings (FILE *f, char **strings, size_t size)
{
  *strings = (char *) malloc (size);
  bool successful = (*strings != NULL);
  if (successful)
    {
      size_t num_bytes = fread (*strings, 1, size, f);
      successful = (num_bytes == size);
    }
  return successful;
}

// local variables:
// c-file-style: "gnu"
// end:
