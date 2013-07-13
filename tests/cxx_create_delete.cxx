// Copyright (C) 2012 Khaled Hosny and Barry Schwartz
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

#include <libunicodenames++.h>
#include <stdlib.h>

using namespace libunicodenames;

int
main (int argc, char *argv[])
{
  if (argc != 2)
    abort ();

  int exit_code = 0;
  try
  {
    unicodenames db1 (argv[1]);
    unicodenames *db2 = new unicodenames (argv[1]);
    delete db2;
  }
  catch (unicodenames_exception & e)
  {
    exit_code = 1;
  }
  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
