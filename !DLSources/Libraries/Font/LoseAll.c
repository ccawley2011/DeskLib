/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Font.c.LoseAll
    Author:  Copyright � 1993 Jason Williams
    Version: 1.00 (29 Jun 1993)
    Purpose: Releases all font claims which have been counted in the given
             font_array. Typically used to release all fonts found by the
             Template loading process. (See Font.h, Template.h, Window.h)
*/

#include "DeskLib:Font.h"

extern void Font_LoseAllFonts(font_array *fonts)
{
  int i;

  for (i = 0; i < 256; i++)
    while (fonts->fonts[i] > 0)           /* Lose all instances of this font */
    {
      Font_LoseFont(i);
      fonts->fonts[i]--;            /* Decrement count until it reaches zero */
    }
}

