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
  typedef struct unicodenames_names___db *unicodenames_names_db;

  /* Open a names db. */
  unicodenames_names_db unicodenames_names_db_open (const char *filename);

  /* Close a names db. */
  void unicodenames_names_db_close (unicodenames_names_db handle);

  /* Retrieve the name of a Unicode codepoint. */
  const char *unicodenames_name (unicodenames_names_db handle,
                                 unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. */
  const char *unicodenames_annotation (unicodenames_names_db handle,
                                       unsigned int codepoint);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class unicodenames
{
private:

  unicodenames_names_db db;

public:

  inline unicodenames (const char *filename)
  {
    db = unicodenames_names_db_open (filename);
    if (!db)
      // FIXME: Is this what really should be thrown here? It may
      // change in the future.
      throw "unicodenames constructor failed";
  }

  inline ~ unicodenames ()
  {
    unicodenames_names_db_close (db);
  }

  inline const char *name (unsigned int codepoint)
  {
    return unicodenames_name (db, codepoint);
  }

  inline const char *annotation (unsigned int codepoint)
  {
    return unicodenames_annotation (db, codepoint);
  }
};

#endif /* __cplusplus */

#endif /* _LIBUNICODENAMES_H */

/* local variables:    */
/* c-file-style: "gnu" */
/* end:                */
