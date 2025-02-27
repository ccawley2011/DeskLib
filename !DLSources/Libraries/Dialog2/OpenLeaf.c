/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Dialog2.OpenLeaf.c
    Author:  Copyright � 1994 Julian Smith
    Version: 1.03 (13 Mar 1995)
    Purpose: Dialogue box handling
*/


#include "DeskLib:WimpSWIs.h"

#include "Defs.h"


BOOL	Dialog2_OpenDialogMenuLeaf( event_pollblock *event, dialog2_block *dialog2)
{

if ( !dialog2)	return ERROR;

Dialog2__CommonOpenMenuCode( dialog2);	/* Close any previous menuleaf etc.	*/

dialog2->flags.data.type = dialog2_type_MENULEAF;
Dialog2__CommonOpenCode( dialog2);

Wimp_CreateSubMenu(
	(menu_ptr) dialog2->window,
	event->data.message.data.words[1],
	event->data.message.data.words[2]
	);

return NOERROR;
}



