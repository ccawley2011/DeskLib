/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pane2.Show.c
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

extern void Pane2_Show(window_handle mainwindow, window_openpos openpos)
{
 /*
  * Opens the main window 'mainwindow' and all its attached pane windows
  * according to 'openpos'
  * Use in the same manner to Window_Show
  */
  main_listelement *mainelement;
  pane_listelement *paneelement;
  window_state panestate;
  window_state mainstate;
  window_handle lastbehind;

 /*
  * find element for main window and return if mainwindow not present
  */
  mainelement = FindMainWindow(mainwindow);
  if(mainelement == NULL)
     return; /* not found */

 /*
  * open main window
  */
  Window_Show(mainelement->mainwindow, openpos);
  Wimp_GetWindowState(mainelement->mainwindow, &mainstate);

 /*
  * level where first window should open behind
  */
  lastbehind = mainstate.openblock.behind;

 /*
  * find first pane window
  */
  paneelement = LinkList_FirstItem(&(mainelement->paneanchor));

 /*
  * open all pane windows
  */
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

}
