/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for 
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #                                      
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pane2.PaneOpenH.c
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

/******************************************************************************/

extern BOOL PaneOpenEventHandler(event_pollblock *event, void *reference)
{
 /*
  * event handler for panes that can be moved (!ArtWorks style)
  * records movement and updates paneoffset
  */
  window_state panestate;
  window_state mainstate;
  pane_listelement *paneelement = reference;

  Wimp_OpenWindow(&(event->data.openblock));

 /*
  * get positions of main and pane windows
  */
  Wimp_GetWindowState(paneelement->panewindow, &panestate);
  Wimp_GetWindowState(paneelement->mainwindow, &mainstate);

 /*
  * update pane offset
  */
  if(paneelement->paneflags.data.mainright)
     paneelement->paneoffset.x = panestate.openblock.screenrect.min.x -
                                 mainstate.openblock.screenrect.max.x;
  else
     paneelement->paneoffset.x = panestate.openblock.screenrect.min.x -
                                 mainstate.openblock.screenrect.min.x;


  if(paneelement->paneflags.data.maintop) /* pane fixed to top of window */
     paneelement->paneoffset.y = mainstate.openblock.screenrect.max.y;

  else /* pane fixed to bottom of window */
     paneelement->paneoffset.y = mainstate.openblock.screenrect.min.y;

  if(paneelement->paneflags.data.panetop) /* pane fixed using top of pane */
     paneelement->paneoffset.y -= panestate.openblock.screenrect.max.y;

  else /* pane fixed using bottom of pane */
     paneelement->paneoffset.y -= panestate.openblock.screenrect.min.y;


  return(TRUE);
}
