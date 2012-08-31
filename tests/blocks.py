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

def make_patch(db, i):
    name = db.name(i)
    patch = None
    if name is not None:
        patch = "@@\t{:04X}\t{}\t{:04X}".format(db.block_start(i),
                                                db.name(i),
                                                db.block_end(i))
    return patch

db_file = sys.argv[1]
nameslist_file = sys.argv[2]
print(db_file)
print(nameslist_file)

db = unicodenames.unicodeblocks(db_file)
nameslist = file(nameslist_file).read()

failure_count = 0

for i in range(0, db.num_blocks()):
    patch = make_patch(db, i)
    if nameslist.find(patch) < 0:
        print("Failure: block #" + str(i))
        failure_count += 1
    i += 1

print("num blocks = " + str(db.num_blocks()))
print("failure_count = " + str(failure_count))

exit_code = 0
if failure_count != 0 or db.num_blocks() <= 0:
    exit_code = 1

exit(exit_code)
