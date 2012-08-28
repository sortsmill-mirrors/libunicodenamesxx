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

# ------------------------------------------------------------------
# FIXME: Include a test that the patches are complete -- that they
# cover the entire annotation.

# FIXME: Include a test that the patches do not overflow -- that they
# cover only the annotation and nothing past it.


import unicodenames
import random, string, sys

def make_patch(db, codepoint):
    name = db.name(codepoint)
    annot = db.annotation(codepoint)
    patch = None
    if name is not None and annot is not None:
        patch = "{:04X}\t{}\n{}".format(codepoint, name, annot)
    return patch

db_file = sys.argv[1]
nameslist_file = sys.argv[2]
random_codepoint_count = int(sys.argv[3])

random.seed()

db = unicodenames.unicodenames(db_file)
nameslist = file(nameslist_file).read()

failure_count = 0

# Test the codepoints up to 0x10FFFF.
codepoint = 0
while codepoint <= 0x10FFFF:
    patch = make_patch(db, codepoint)
    if patch is not None:
        if nameslist.find(patch) < 0:
            print("Failure: codepoint = " + str(codepoint))
            failure_count += 1
    codepoint += 1

# Test random codepoints.
i = 0
while i <= random_codepoint_count:
    codepoint = random.randint(0, 0xffffffff)
    #print codepoint
    patch = make_patch(db, codepoint)
    if patch is not None:
        if nameslist.find(patch) < 0:
            print("Failure: codepoint = " + str(codepoint))
            failure_count += 1
    i += 1

print("failure_count = " + str(failure_count))

exit_code = 0
if failure_count != 0:
    exit_code = 1

exit(exit_code)
