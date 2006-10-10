/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pane2.AddMain.c
    Author:  Copyright � 1995 Andrew Sellors.
    Version: 1.04 (4th August 1995)
    Purpose: Handles windows with panes.
*/

#include "DeskLib:Pane2.h"
#include "Pane2Defs.h"
#include "Desklib:Event.h"
#include "DeskLib:Template.h"
#include "Desklib:EventMsg.h"
#include "Desklib:Error.h"

#include <stdlib.h>


/******************************************************************************/

extern BOOL Pane2_AddMain(window_handle mainwindow)
{
 /*
  * initialises 'mainwindow' with the library as a main window that can have
  * panes attached to it.
  */
  main_listelement *mainelement;

 /*
  * malloc memory for list element and return FALSE if fails
  */
  mainelement = malloc(sizeof(main_listelement));
  if(mainelement == NULL)
     return(FALSE); /* failed */

 /*
  * initialise list headers
  */
  LinkList_Init(&(mainelement->header));
  LinkList_Init(&(mainelement->paneanchor));

 /*
  * add main window handle to list element
  */
  mainelement->mainwindow = mainwindow;
  mainelement->invalideventdata = FALSE;

 /*
  * add list element to end of list
  */
  LinkList_AddToTail(&main_anchor, &(mainelement->header));

 /*
  * install open window event handler for main window
  */
  Event_Claim(event_OPEN, mainwindow, event_ANY, OpenEventHandler, mainelement);

 /*
  * install message handler on mode change so that main window is opened before
  * status is read so that panes open in correct place
  */
  EventMsg_Claim(message_MODECHANGE, event_ANY, ModeChangeMessageHandler, mainelement);

  return(TRUE);
}
