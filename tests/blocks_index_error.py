#  Copyright (C) 2012 Barry Schwartz
#
#  This file is part of LibUnicodeNames.
#
#  LibUnicodeNames is free software: you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation, either version 3 of
#  the License, or (at your option) any later version.
#
#  LibUnicodeNames is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with LibUnicodeNames.  If not, see
#  <http://www.gnu.org/licenses/>.

import unicodenames
import sys

db_file = sys.argv[1]
print(db_file)

db = unicodenames.unicodeblocks(db_file)

failure_count = 0

try:
    exit_code = 1
    print(db.name(-1))
except IndexError as e:
    print(e)
    exit_code = 0

if exit_code == 0:
    try:
        exit_code = 1
        print(db.name(db.num_blocks()))
    except IndexError as e:
        print(e)
        exit_code = 0

exit(exit_code)
