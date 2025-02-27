/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Pointer.Restrict.c
    Author:  Copyright � 1994 Lee Atkinson
    Version: 1.00 (28 Sep 1994)
    Purpose: Restrict pointer to window or icon
*/

#include "DeskLib:Error.h"
#include "DeskLib:Icon.h"
#include "DeskLib:KernelSWIs.h"
#include "DeskLib:Screen.h"
#include "DeskLib:Wimp.h"
#include "DeskLib:WimpSWIs.h"
#include "DeskLib:Pointer.h"


typedef char byte;

static void Lower2Bytes(int integer,byte *byte0,byte *byte1)
                             /* extracts lowest 2 bytes from input integer */
{
 union
      {
       int integer;
       byte bytes[2];
      }
       u;
 u.integer=integer;
 *byte0=u.bytes[0]; /* lowest byte */
 *byte1=u.bytes[1]; /* next lowest byte */
}

os_error *Pointer_RestrictToWindow(window_handle window)
{
 byte         box[9]={1};
 window_state wstate;
 Wimp_GetWindowState(window,&wstate); /* find window size & pos. */
 Lower2Bytes(wstate.openblock.screenrect.min.x,&box[1],&box[2]);
 Lower2Bytes(wstate.openblock.screenrect.min.y,&box[3],&box[4]);
 Lower2Bytes(wstate.openblock.screenrect.max.x,&box[5],&box[6]);
 Lower2Bytes(wstate.openblock.screenrect.max.y,&box[7],&box[8]);
 return OS_Word(osword_DEFINEPOINTERANDMOUSE,box);
}

os_error *Pointer_RestrictToIcon(window_handle window,icon_handle icon)
{
 byte      box[9]={1};
 wimp_rect rect;
 Icon_ScreenPos(window,icon,&rect);
 Lower2Bytes(rect.min.x,&box[1],&box[2]);
 Lower2Bytes(rect.min.y,&box[3],&box[4]);
 Lower2Bytes(rect.max.x,&box[5],&box[6]);
 Lower2Bytes(rect.max.y,&box[7],&box[8]);
 return OS_Word(osword_DEFINEPOINTERANDMOUSE,box);
}

os_error *Pointer_RestrictToRect(wimp_rect rect)
{
 byte box[9]={1};
 Lower2Bytes(rect.min.x,&box[1],&box[2]);
 Lower2Bytes(rect.min.y,&box[3],&box[4]);
 Lower2Bytes(rect.max.x,&box[5],&box[6]);
 Lower2Bytes(rect.max.y,&box[7],&box[8]);
 return OS_Word(osword_DEFINEPOINTERANDMOUSE,box);
}

os_error *Pointer_Unrestrict(void)
{
 byte box[9]={1,0,0,0,0};
 Screen_CacheModeInfo(); /* find screen size */
 Lower2Bytes((screen_size.x-1),&box[5],&box[6]);
 Lower2Bytes((screen_size.y-1),&box[7],&box[8]);
 return OS_Word(osword_DEFINEPOINTERANDMOUSE,box);
}
