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
    id_string = "libunicodenames blocks db      "
    db_version = 1

    BINMODE = "rw"
    block_count = 0
}

/^@@\t/ {
    match($0, /^@@\t(.*)\t(.*)\t(.*)/, field)
    start_point[block_count] = strtonum("0x" field[1])
    description[block_count] = field[2]
    end_point[block_count] = strtonum("0x" field[3])
    block_count++
    next
}

END {
    printf("%s%c", id_string, 0)
    print_uint(db_version)
    print_uint(block_count)
    print_uint_array(start_point)
    print_uint_array(end_point)
    strings_size = print_offsets()
    print_uint(strings_size)
    print_strings()
}

function print_offsets()
{
    offset = 0
    for (i = 0; i < block_count; i++) {
        print_uint(offset)
        offset += length(description[i]) + 1
    }
    return offset
}

function print_strings()
{
    for (i = 0; i < block_count; i++)
        printf("%s%c", description[i], 0)
}

function print_uint_array(a)
{
    for (i = 0; i < block_count; i++)
        print_uint(a[i])
}

function print_uint(n)
{
    n = n + 0
    printf("%c", and(n, 255))
    printf("%c", and(rshift(n,8), 255))
    printf("%c", and(rshift(n,16), 255))
    printf("%c", and(rshift(n,24), 255))
}
