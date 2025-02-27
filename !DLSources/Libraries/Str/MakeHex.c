/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Str.MakeHex.c
    Author:  Copyright � 1994 Tim Browse
    Version: 1.00 (06 Mar 1994)
    Purpose: Convert a number to a hex digit character.
*/

#include "DeskLib:Str.h"

char Str_MakeHex(int n)
{
  if ((n >=0) && (n <= 9))
    return ('0' + (char) n);
  else if ((n >= 10) && (n <= 15))
    return ('A' + (char) (n - 10));
  else return '?';
}

