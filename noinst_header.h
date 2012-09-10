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

#ifndef TEXTDOMAIN
# error You must define TEXTDOMAIN.
#endif

#include "config.h"
#include "libunicodenames.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "libgettext.h"

#define _(String) dgettext (TEXTDOMAIN, String)

bool __string_matches (FILE *f, const char *s);
bool __read_uint (FILE *f, unsigned int *i);
bool __read_uint_array (FILE *f, unsigned int **i_array, size_t size);
bool __read_strings (FILE *f, char **strings, size_t size);

// local variables:
// c-file-style: "gnu"
// end:
