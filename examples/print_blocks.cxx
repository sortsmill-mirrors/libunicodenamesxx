/*
 * Prints the start points, end points, and names of the Unicode
 * blocks.
 *
 * This is one of the example programs from the manpage.
 *
 * Copyright (C) 2013 Khaled Hosny and Barry Schwartz
 * 
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved.  This file is offered as-is,
 * without any warranty.
 */

#include <libunicodenames++.h>
#include <cstdio>
#include <cstdlib>
#include <clocale>

int
main (int argc, char **argv)
{
  std::setlocale (LC_ALL, "");
  char *dbfile = libunicodenames::find_blocks_db (0);
  libunicodenames::unicodeblocks db (dbfile);
  delete dbfile;
  size_t numblocks = db.num_blocks ();
  for (int i = 0; i < numblocks; i++)
    {
      unsigned int start = db.block_start (i);
      unsigned int end = db.block_end (i);
      const char *name = db.name (i);
      if (name == 0)
	exit (2);
      std::printf ("--\ni: %u\nstart: %d\nend: %d\n"
		   "block name: %s\n",
		   (unsigned int) i, start, end, name);
    }
}
