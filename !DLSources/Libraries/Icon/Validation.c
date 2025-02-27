/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Icon/Validation.c
    Author:  Copyright � 1992 Jason Williams
    Version: 1.01 (12 Dec 1992)
             1.02 (25 Oct 2007) Moved from Validation to Icon module
    Purpose: Scanning of validation strings for various fields
*/

#include "DeskLib:Core.h"
#include "DeskLib:Icon.h"

extern int Icon_ScanValidationString(const char *string, char tag)
{
  register int  index;
  register char trytag;

  if ((int) string <= 0 || string[0] < 32)  /* Invalid pointer/NULL string   */
    return(0);

  if (tag >= 'a' && tag <= 'z')
    tag &= 0xdf;                            /* Force to uppercase to compare */

  index = -1;
  while (TRUE)
  {
    if (string[++index] < 32)               /* End of string-still not found */
      return(0);

    if (string[index] >= 'a' && string[index] <= 'z')
      trytag = string[index] & 0xdf;
    else
      trytag = string[index];               /* Force to uppercase to compare */

    if (trytag == tag)
    {
      if (string[index + 1] < 32)
        return(0);                         /* No chars following tag!        */
      else
        return(index + 1);                 /* Found, so return index         */
    }

    while (string[index] != ';')            /* Scan for ';' - item seperator */
      if (string[++index] < 32)                                 /* not found */
        return(0);
  }
}
