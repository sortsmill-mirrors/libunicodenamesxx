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


#ifndef _LIBUNICODENAMES_H
#define _LIBUNICODENAMES_H

#ifdef __cplusplus
extern "C"
{
#endif

  /* A names db handle. */
  typedef struct libunicodenames_names___db *libunicodenames_names_db;

  /* Open a names db. */
  libunicodenames_names_db libunicodenames_names_db_open (const char *filename);

  /* Close a names db. */
  void libunicodenames_names_db_close (libunicodenames_names_db handle);

  /* Retrieve the name of a Unicode codepoint. */
  const char *libunicodenames_name (libunicodenames_names_db handle,
                                   unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. */
  const char *libunicodenames_annot (libunicodenames_names_db handle,
                                    unsigned int codepoint);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class unicodenames
{
private:

  libunicodenames_names_db db;

public:

  inline unicodenames (const char *filename)
  {
    db = libunicodenames_names_db_open (filename);
    if (!db)
      // FIXME: Is this what really should be thrown here? It may
      // change in the future.
      throw "unicodenames constructor failed";
  }

  inline ~ unicodenames ()
  {
    libunicodenames_names_db_close (db);
  }

  inline const char *name (unsigned int codepoint)
  {
    return libunicodenames_name (db, codepoint);
  }

  inline const char *annot (unsigned int codepoint)
  {
    return libunicodenames_annot (db, codepoint);
  }
};

#endif /* __cplusplus */

#endif /* _LIBUNICODENAMES_H */

/* local variables:    */
/* c-file-style: "gnu" */
/* end:                */
