/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Icon.GetFgCol.c
    Author:  Copyright � 1994 Tim Browse
    Version: 1.00 (05 Mar 1994)
    Purpose: Retrieve the foreground colour of an icon.
*/

#include "DeskLib:Wimp.h"
#include "DeskLib:WimpSWIs.h"
#include "DeskLib:Icon.h"
#include "DeskLib:Str.h"


int Icon_GetFgCol(icon_block *icon)
{
  int colour;

  /* Straightforward case first...*/
  if (!icon->flags.data.font)
    return icon->flags.data.foreground;

  /* Icon is anti-aliased - read font validation string colours */
  colour = Validation_ScanString(icon->data.indirecttext.validstring,
                                 iconvalid_FONTCOLOURS);

  /* No colours specified - use default */
  if (colour == 0)
    return colour_BLACK;

  /* Decode second colour digit */
  colour = Str_DecodeHex(icon->data.indirecttext.validstring[colour+1]);

  /* Limit to legal value */
  if (colour == -1)
    colour = colour_BLACK;

  return colour;
}

