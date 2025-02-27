/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pane2.CAddPane.c
    Author:  Copyright � 1995 Andrew Sellors.
    Version: 1.03 (4th July 1995)
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

extern window_handle Pane2_CreateAndAddPane(const char *windowname, int maxtitlesize,
                                            window_handle mainwindow,
                                            wimp_point *paneoffset,
                                            wimp_point *panesize,
                                            int flags)
{
 /*
  * Creates pane window as Window_Create and adds to the main window
  * 'mainwindow'.
  * If 'paneoffset' is not NULL then this is taken as the offset between the
  * pane and the main window instead of the positions in the template.
  * If 'panesize' is not NULL then this is taken as the size of the pane
  * instead of the size in the template.
  * The window handle is returned or 0 if window cannot be created.
  */
  window_handle panewindow;

  panewindow = Window_Create(windowname, maxtitlesize);

  if(panewindow != 0){

     if(!Pane2_AddPane(mainwindow, panewindow, paneoffset, panesize, flags)){

        Window_Delete(panewindow);  /* delete panewindow if could not be added */
        panewindow = 0;

     }

  }

  return(panewindow);
}
