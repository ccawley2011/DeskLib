/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Str.DecodeHex.c
    Author:  Copyright � 1994 Tim Browse
    Version: 1.00 (06 Mar 1994)
    Purpose: Convert a hex digit character to a number.
*/

#include <ctype.h>

#include "DeskLib:Str.h"


int Str_DecodeHex(char digit)
{
  digit = toupper(digit);

  if ((digit >= '0') && (digit <= '9'))
    return (int) (digit - '0');
  else if ((digit >= 'A') && (digit <= 'F'))
    return (int) ((digit - 'A') + 10);
  else return -1;
}

