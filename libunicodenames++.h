// Copyright (C) 2012 Khaled Hosny and Barry Schwartz
//
// This file is part of LibUnicodeNames++.
// 
// LibUnicodeNames++ is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
// 
// LibUnicodeNames++ is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with LibUnicodeNames++.  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef _LIBUNICODENAMESXX_H
#define _LIBUNICODENAMESXX_H 1

#include <libunicodenames.h>
#include <exception>

namespace libunicodenames
{

  class unicodenames_exception:public std::exception
  {
  public:
    virtual const char *what () throw ();
  };

  class memory_exhausted:public unicodenames_exception
  {
  public:
    virtual const char *what () throw ();
  };

  class open_failed:public unicodenames_exception
  {
  public:
    virtual const char *what () throw ();
  };

  class index_error:public unicodenames_exception
  {
  public:
    virtual const char *what () throw ();
  };

  char *find_names_db (const char *locale_base = 0);
  char *find_blocks_db (const char *locale_base = 0);

  class unicodenames
  {
  private:
    uninm_names_db db;

  public:
      unicodenames (const char *filename);
     ~unicodenames ();

    const char *name (unsigned int codepoint)
    {
      return uninm_name (db, codepoint);
    }

    const char *annotation (unsigned int codepoint)
    {
      return uninm_annotation (db, codepoint);
    }
  };				/* class unicodenames */

  class unicodeblocks
  {
  private:
    uninm_blocks_db db;

    void check_index (int i)
    {
      if (i < 0 || uninm_num_blocks (db) <= (size_t) i)
	throw index_error ();
    }

  public:
      unicodeblocks (const char *filename);
    ~unicodeblocks ();

    size_t num_blocks ()
    {
      return uninm_num_blocks (db);
    }

    unsigned int block_start (int i);
    unsigned int block_end (int i);
    const char *name (int i);
  };				/* class unicodeblocks */

};				/* namespace libunicodenames */

#endif /* _LIBUNICODENAMESXX_H */

// local variables:
// c-file-style: "gnu"
// end:
