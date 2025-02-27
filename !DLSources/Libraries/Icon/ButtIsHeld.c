/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Icon.ButtIsHeld.c
    Author:  Copyright � 1994 Lenny
    Version: 0.01 (23 Nov 1994)
    Purpose: Returns TRUE if a mouse button is held down.
    History: 0.01 (23 Nov 94) : Added 'Icon_ButtonIsHeld()'

*/

/* --- LOAD HEADERS ------------------------------------------------------ */

/* --- DeskLib ----------------------------------------------------------- */
#include "DeskLib:WimpSWIs.h"          /* Low-level WIMP commands          */
#include "DeskLib:Icon.h"

/* === FUNCTION DEFINITIONS ============================================== */

extern BOOL Icon_ButtonIsHeld(void)
/*
 *  Returns TRUE if a mouse button is held down.
 *
 *  Usage : With inc/dec type icons where auto-repeat is required for an
 *          icon using a 3D effect, with a button type 'Click'.
 *          It prevents the annoying repeated indent-outdent effect
 *          produced when using a button type 'Auto-Repeat' with a 3D
 *          icon.
 *  It currently returns TRUE, even if the pointer is no longer over the
 *  icon, provided the button is still held down.
 */
{
  mouse_block       mouse;

  Wimp_GetPointerInfo(&mouse);  /*  Get mouse button info  */

  return ((mouse.button.value & 0x07) != 0);

}

/***************************************************************************/
