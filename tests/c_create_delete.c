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


#include <libunicodenames.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  if (argc != 2)
    abort ();

  int exit_code = 1;
  uninm_names_db db = uninm_names_db_open (argv[1]);
  if (db != NULL)
    {
      exit_code = 0;
      uninm_names_db_close (db);
    }
  return exit_code;
}
