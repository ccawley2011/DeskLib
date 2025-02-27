/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Str.stricmpcr.c
    Author:  Copyright � 1994 Tim Browse
    Version: 1.00 (06 Mar 1994)
    Purpose: Version of stricmp that works on CR-terminated strings.
*/

#include <ctype.h>

#include "DeskLib:Str.h"

int stricmpcr(const char *s1, const char *s2)
{
  char ch1 = 0,
       ch2 = 0;

  for(;;)
  {
    if ((*s1 < 32) && (*s2 < 32))
      return 0; /* s1 and s2 are equal */

    ch1 = toupper(*s1);
    ch2 = toupper(*s2);

    if (ch1 != ch2)
      return (int) (ch1 - ch2);
    s1++;
    s2++;
  }
}
