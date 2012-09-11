/*
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
*/

#ifndef _LIBUNICODENAMES_H
#define _LIBUNICODENAMES_H 1

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /* A names db handle. */
  typedef struct uninm_names___db *uninm_names_db;

  /* A blocks db handle. */
  typedef struct uninm_blocks___db *uninm_blocks_db;

  /* Get the path of the names db for the current locale. The string
     should be freed by the caller. If locale_base is non-NULL, then
     use it as the base directory for MO files; otherwise use the
     compiled-in locale directory. */
  char *uninm_find_names_db (const char *locale_base);

  /* Get the path of the blocks db for the current locale. The string
     should be freed by the caller. If locale_base is non-NULL, then
     use it as the base directory for MO files; otherwise use the
     compiled-in locale directory. */
  char *uninm_find_blocks_db (const char *locale_base);

  /* Open a names db. */
  uninm_names_db uninm_names_db_open (const char *filename);

  /* Open a blocks db. */
  uninm_blocks_db uninm_blocks_db_open (const char *filename);

  /* Close a names db. */
  void uninm_names_db_close (uninm_names_db handle);

  /* Close a blocks db. */
  void uninm_blocks_db_close (uninm_blocks_db handle);

  /* Retrieve the name of a Unicode codepoint. The string must not
     be freed by the caller. */
  const char *uninm_name (uninm_names_db handle, unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. The string must
     not be freed by the caller. */
  const char *uninm_annotation (uninm_names_db handle,
				unsigned int codepoint);

  size_t uninm_num_blocks (uninm_blocks_db handle);

  unsigned int uninm_block_start (uninm_blocks_db handle, int i);

  unsigned int uninm_block_end (uninm_blocks_db handle, int i);

  const char *uninm_block_name (uninm_blocks_db handle, int i);

#ifdef __cplusplus
}
#endif

#endif				/* _LIBUNICODENAMES_H */

// local variables:
// c-file-style: "gnu"
// end:
