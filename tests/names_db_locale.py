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
import locale, os, sys

my_locale = sys.argv[1]
codepoint = int(sys.argv[2], 16)
localedir = None if sys.argv[3] == "" else sys.argv[3]

exit_code = 0

try:
    loc = locale.setlocale(locale.LC_MESSAGES, my_locale)
except:
    print('locale not supported; skipping test')
    exit_code = 77

try:
    print(loc)
    names_db = unicodenames.find_names_db(localedir)
    print(os.path.basename(names_db))
    db = unicodenames.unicodenames(names_db)
    print(db.name(codepoint))
    del db
except:
    print('exception caught')
    exit_code = 1

exit(exit_code)
