/*
 * Prints names and annotations corresponding to code points 0 to 999.
 *
 * This is one of the example programs from the manpage.
 *
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
#include <clocale>

int
main (int argc, char **argv)
{
  std::setlocale (LC_ALL, "");
  char *dbfile = libunicodenames::find_names_db (0);
  libunicodenames::unicodenames db (dbfile);
  delete dbfile;
  for (int codepoint = 0; codepoint <= 999; codepoint++)
    {
      const char *name = db.name (codepoint);
      const char *annot = db.annotation (codepoint);
      name = (name == 0) ? "--none--" : name;
      annot = (annot == 0) ? "--none--" : annot;
      std::printf ("--\ncode point: %u\nname: %s\n"
                   "annotation:\n%s\n",
                   codepoint, name, annot);
    }
}

// local variables:
// indent-tabs-mode: nil
// end:
