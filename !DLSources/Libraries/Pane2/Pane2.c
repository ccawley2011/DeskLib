/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pane2.Pane2.c
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
#include "DeskLib:Screen.h"

#include <stdlib.h>

/* base of linked list */
linklist_header main_anchor = {NULL, NULL};

/******************************************************************************/

extern BOOL OpenEventHandler(event_pollblock *event, void *reference)
{
 /*
  * event handler to open the pane windows in sequence each behind each other
  * and the main window last behind all the panes
  */

  return(OpenWindow(&(event->data.openblock), (main_listelement *)reference));

}

/******************************************************************************/

extern BOOL OpenWindow(window_openblock *openblock, main_listelement *mainelement)
{
 /*
  * opens the pane windows in sequence each behind each other
  * and the main window last behind all the panes
  */
  window_state panestate;
  window_state mainstate;
  pane_listelement *paneelement;
  window_handle lastbehind;
  window_handle tempbehind;

 /*
  * check if there are any pane windows attached at the moment
  */
  if(mainelement->paneanchor.next == NULL)
     return(FALSE);

 /*
  * get info about main window
  */
  Wimp_GetWindowState(mainelement->mainwindow, &mainstate);

 /*
  * check if bottom or right hand side are anywhere near the edge of the screen
  * or if window has been toggled to full size or mode was changed
  * makes pane go to correct place by opening window and re-reading the position
  * as sometimes the position in the event data is incorrect.
  */
  Screen_CacheModeInfo();
  if( (openblock->screenrect.max.x > (screen_size.x - 100)) ||
      (openblock->screenrect.min.y < 100) ||
       mainstate.flags.data.istoggling ||
       mainelement->invalideventdata ){

    /*
     * set window level in openblock to old value and remember new value
     */
     tempbehind = openblock->behind;
     openblock->behind = mainstate.openblock.behind;

    /*
     * openwindow and re-read window state to get correct position
     */
     Wimp_OpenWindow(openblock);
     Wimp_GetWindowState(mainelement->mainwindow, &mainstate);
     mainstate.openblock.behind = tempbehind;

  }
  else
     mainstate.openblock = *openblock;

  if(mainstate.flags.data.istoggling || mainelement->invalideventdata)
     mainelement->invalideventdata = FALSE;

 /*
  * level where first window should open behind
  */
  lastbehind = mainstate.openblock.behind;

 /*
  * find first pane window
  */
  paneelement = LinkList_FirstItem(&(mainelement->paneanchor));

  while(paneelement != NULL){

    /*
     * get pane window info
     */
     Wimp_GetWindowState(paneelement->panewindow, &panestate);

    /*
     * y position of pane
     */
     if(paneelement->paneflags.data.maintop) /* pane fixed to top of window */
        panestate.openblock.screenrect.max.y = mainstate.openblock.screenrect.max.y -
                                               paneelement->paneoffset.y;
     else /* pane fixed to bottom of window */
        panestate.openblock.screenrect.max.y = mainstate.openblock.screenrect.min.y -
                                               paneelement->paneoffset.y;

     if(!paneelement->paneflags.data.panetop) /* pane fixed using bottom of pane */
        panestate.openblock.screenrect.max.y += paneelement->panesize.y;

     if(paneelement->paneflags.data.vscroll) /* scroll pane vertical */
        panestate.openblock.scroll.y = mainstate.openblock.scroll.y;

    /*
     * y size of pane
     */
     if(paneelement->paneflags.data.vresize){ /* resize pane vertical */

        panestate.openblock.screenrect.min.y = mainstate.openblock.screenrect.min.y;

        if(!paneelement->paneflags.data.vstretch &&
           (mainstate.openblock.screenrect.min.y < panestate.openblock.screenrect.max.y -
                                                   paneelement->panesize.y))

           panestate.openblock.screenrect.min.y = panestate.openblock.screenrect.max.y -
                                                  paneelement->panesize.y;
     }
     else
        panestate.openblock.screenrect.min.y = panestate.openblock.screenrect.max.y -
                                               paneelement->panesize.y;

    /*
     * x position of pane
     */
     if(paneelement->paneflags.data.mainright)
        panestate.openblock.screenrect.min.x = mainstate.openblock.screenrect.max.x +
                                               paneelement->paneoffset.x;
     else
        panestate.openblock.screenrect.min.x = mainstate.openblock.screenrect.min.x +
                                               paneelement->paneoffset.x;

     if(paneelement->paneflags.data.hscroll) /* scroll pane horizontal */
        panestate.openblock.scroll.x = mainstate.openblock.scroll.x;

    /*
     * x size of pane
     */
     if(paneelement->paneflags.data.hresize){ /* resize pane horizontal */

        panestate.openblock.screenrect.max.x = mainstate.openblock.screenrect.max.x;

        if(!paneelement->paneflags.data.hstretch &&
           (mainstate.openblock.screenrect.max.x > panestate.openblock.screenrect.min.x +
                                                   paneelement->panesize.x))

           panestate.openblock.screenrect.max.x = panestate.openblock.screenrect.min.x +
                                                  paneelement->panesize.x;

     }
     else
        panestate.openblock.screenrect.max.x = panestate.openblock.screenrect.min.x +
                                               paneelement->panesize.x;


    /*
     * open pane behind last pane or level where main window should have been
     * if it is the first
     */
     panestate.openblock.behind = lastbehind;
     Wimp_OpenWindow(&panestate.openblock);
     lastbehind = paneelement->panewindow;

    /*
     * find next pane window
     */
     paneelement = LinkList_NextItem(&(paneelement->header));
  }

 /*
  * open main window behind last pane
  */
  mainstate.openblock.behind = lastbehind;
  Wimp_OpenWindow(&mainstate.openblock);


  return(TRUE);
}

/******************************************************************************/

extern BOOL ModeChangeMessageHandler(event_pollblock *event, void *reference)
{
 /*
  * sets flag on mode change so that main window is opened before window state
  * is read
  */

  main_listelement *mainelement = reference;

  UNUSED( event);

  mainelement->invalideventdata = TRUE;

  return(FALSE);
}

/******************************************************************************/

