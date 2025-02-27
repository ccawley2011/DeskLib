/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Misc.strlencr.c
    Author:  Copyright � 1992 Jason Williams
             Thanks to John Winters for supplying the code that I hacked
             changed, hacked, rewrote, and then wrote again from scratch!
    Version: 1.10 (29 Mar 1992)
    Purpose: Find length of CR-terminated string
*/


#include "DeskLib:Str.h"

extern int strlencr(const char *s)
/* return number of bytes needed to store this string, including terminator */
{
  register int index = 0;

  while (s[index] > 31)
    index++;

  return(index);
}
