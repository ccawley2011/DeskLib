/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    LinkList.AddToTail.c
    Author:  Copyright � 1992 Jason Williams
    Version: 1.02 (16 Mar 1992)
    Purpose: Linked list handling functions
*/


#include <stdlib.h>
#include <stdio.h>

#include "DeskLib:LinkList.h"

extern void LinkList_AddToTail(linklist_header *anchor, linklist_header *item)
{
  linklist_header *oldlast;

  oldlast          = anchor->previous;
  item->next       = NULL;                           /* This item is last    */
  item->previous   = oldlast;                        /* Link to end          */

  if (oldlast == NULL)
    anchor->next = item;                  /* First item, so it is 1st & last */
  else
    oldlast->next = item;                            /* link to previous     */
  anchor->previous = item;                           /* And link to header   */
}
