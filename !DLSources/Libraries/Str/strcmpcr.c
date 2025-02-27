/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Template.strcmpcr.c
    Author:  Copyright � 1993 Jason Williams
    Version: 1.00 (16 May 1993)
    Purpose: Compare two CR-terminated strings to see if they match
*/

#include "DeskLib:Str.h"

   /*
    * compares the string pointed to by s1 to the string pointed to by s2.
    * Returns: an integer greater than, equal to, or less than zero, according
    *          as the string pointed to by s1 is greater than, equal to, or
    *          less than the string pointed to by s2.
    */
extern int strcmpcr(const char *s1, const char *s2)
{
  register int index = 0;

  while (s1[index] > 31 && s2[index] > 31)
  {
    if (s1[index] > s2[index])
      return(1);
    else
      if (s1[index] < s2[index])
        return(-1);

    index++;
  }

  if (s1[index] > 31)        /* s1 is longer than s2, so is greater than */
    return(1);

   if (s2[index] > 31)       /* s2 is longer than s1, so result is less than */
    return(-1);

  return(0);                 /* Strings exactly match */
}
