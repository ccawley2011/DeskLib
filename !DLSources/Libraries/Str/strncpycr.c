/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for 
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #                                      
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Misc.strncpycr.c
    Author:  Copyright � 1994 Jason Howat
    Version: 1.00 (18 Apr 1994)
    Purpose: Copies a CR-terminated string - note that this will change the
             terminator of the result to a NUL (0).
*/

#include "DeskLib:StringCR.h"


extern char *strncpycr(char *s1, char *s2, int n)
{
  register char *end = s1 + n;

  while ((*s2 > 31) && (s1 != end))
    *(s1++)  = *(s2++);

  if(s1 != end)                         /* copy terminator if space */
    *s1 = 0;

  return(s1);
}
