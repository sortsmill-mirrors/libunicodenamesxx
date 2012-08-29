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
#define _LIBUNICODENAMES_H

#ifdef __cplusplus
extern "C"
{
#endif

  /* A names db handle. */
  typedef struct unicodenames_names___db *unicodenames_names_db;

  /* Get the path of the names db for the current locale. The string
     should be freed by the caller. */
  char *unicodenames_names_db_for_current_locale (void);

  /* Open a names db. */
  unicodenames_names_db unicodenames_names_db_open (const char *filename);

  /* Close a names db. */
  void unicodenames_names_db_close (unicodenames_names_db handle);

  /* Retrieve the name of a Unicode codepoint. The string must not
     be freed by the caller. */
  const char *unicodenames_name (unicodenames_names_db handle,
                                 unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. The string must
     not be freed by the caller. */
  const char *unicodenames_annotation (unicodenames_names_db handle,
                                       unsigned int codepoint);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <exception>

namespace libunicodenames
{

  class unicodenames_exception:public std::exception
  {
    virtual const char *what () throw ();
  };

  class memory_exhausted:public unicodenames_exception
  {
    virtual const char *what () throw ();
  };

  class open_failed:public unicodenames_exception
  {
    virtual const char *what () throw ();
  };

  char *names_db_for_current_locale ();

  class unicodenames
  {
  private:
    unicodenames_names_db db;

  public:
    unicodenames (const char *filename);
     ~unicodenames ();

    const char *name (unsigned int codepoint)
    {
      return unicodenames_name (db, codepoint);
    }

    const char *annotation (unsigned int codepoint)
    {
      return unicodenames_annotation (db, codepoint);
    }
  };

};                              // libunicodenames

#endif /* __cplusplus */

#endif /* _LIBUNICODENAMES_H */

/* local variables:    */
/* c-file-style: "gnu" */
/* end:                */
