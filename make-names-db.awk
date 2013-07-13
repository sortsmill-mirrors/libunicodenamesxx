#! /usr/bin/gawk -f
#
# This script uses GNU Awk features.

#  Copyright (C) 2012 Khaled Hosny and Barry Schwartz
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


BEGIN {
    # 31 bytes:  1234567890123456789012345678901
    id_string = "libunicodenames names db       "
    db_version = 1

    BINMODE = "rw"
    codepoint = -1
    codepoint_count = 0
}

/^[[:xdigit:]]+\t/ {
    match($0, /^([[:xdigit:]]+)\t(.*)/, field)
    codepoint = strtonum("0x" field[1])
    uniname[codepoint] = field[2]
    uniannot[codepoint] = ""
    uniannot_prefix = ""
    codepoint_count++
    next
}

/^[[:graph:]]/ {
    codepoint = -1
    next
}

0 <= codepoint {
    sub(/^\t\*/, "\t•", $0)
    sub(/^\tx/, "\t→", $0)
    sub(/^\t:/, "\t≍", $0)
    sub(/^\t#/, "\t≅", $0)
    uniannot[codepoint] = uniannot[codepoint] uniannot_prefix $0
    uniannot_prefix = "\n"
    next
}

END {
    printf("%s%c", id_string, 0)
    print_uint(db_version)
    print_uint(codepoint_count)
    print_codepoint_array(uniname)
    annot_offset = print_offsets(uniname, 0)
    string_section_size = print_offsets(uniannot, annot_offset)
    print_uint(string_section_size)
    print_strings(uniname)
    print_strings(uniannot)
}

function print_codepoint_array(some_unilist)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    for (codepoint in some_unilist)
        print_uint(codepoint)
}

function print_offsets(some_unilist, start_offset)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    offset = start_offset
    for (codepoint in some_unilist) {
        print_uint(offset)
        offset += length(some_unilist[codepoint]) + 1
    }
    return offset
}

function print_strings(some_unilist)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    for (codepoint in some_unilist)
        printf("%s%c", some_unilist[codepoint], 0)
}

function print_uint(n)
{
    n = n + 0
    printf("%c", and(n, 255))
    printf("%c", and(rshift(n,8), 255))
    printf("%c", and(rshift(n,16), 255))
    printf("%c", and(rshift(n,24), 255))
}

# local variables:
# coding: utf-8
# end:
