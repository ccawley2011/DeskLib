/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Icon.GetText.c
    Author:  Copyright � 1992, 1993, 1994 Jason Williams
    Version: 1.02 (22 May 1994)
    Purpose: Retrieves the text/spritename from an icon
    Mods:    29 Jul 1995 JPS - now sets terminter in returned string
                               rather than the icon's buffer.
*/

#include "DeskLib:Wimp.h"
#include "DeskLib:WimpSWIs.h"
#include "DeskLib:Icon.h"

#include <string.h>


extern void Icon_GetText(window_handle w, icon_handle i, char *text)
/*
 * Copies the text string from the icon (sprite name, text, or indirected)
 * into the array pointed to by "text"
 */
{
  icon_block istate;
  const char *buffer;
  int         len = wimp_MAXNAME;
  int         index;

  text[0] = 0;  /* return NULL string if anything goes wrong */

  Wimp_GetIconState(w, i, &istate);
  if (istate.flags.data.indirected)
  {
    if (istate.flags.data.sprite)
        buffer = istate.data.indirectsprite.name;
    else
    {
      buffer = istate.data.indirecttext.buffer;
      len    = istate.data.indirecttext.bufflen;
    }
  }
  else
    buffer = istate.data.text;                           /* text/sprite name */

  strncpy(text, buffer, len);                            /* text/sprite name */

  /* Terminate string at first control character, or at end of buffer */
  index = 0;
  while ((index < len) && (text[index] >= ' '))
    index++;

  if (index < len)
    text[index] = '\0';
  else
    text[len - 1] = '\0';
}
