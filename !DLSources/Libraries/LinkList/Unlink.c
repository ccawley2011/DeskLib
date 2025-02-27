/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    LinkList.Unlink.c
    Author:  Copyright � 1992 Jason Williams
    Version: 1.02 (16 Mar 1992)
    Purpose: Linked list handling functions
*/


#include <stdlib.h>
#include <stdio.h>

#include "DeskLib:LinkList.h"

extern void LinkList_Unlink(linklist_header *anchor, linklist_header *item)
{
  linklist_header *prev, *next;

  next = item->next;
  prev = item->previous;

  if (next == NULL)
    anchor->previous = prev;                            /* was last in list  */
  else
    next->previous   = prev;                            /* was in middle     */

  if (prev == NULL)
    anchor->next = next;                                /* was first in list */
  else
    prev->next   = next;                                /* was in middle     */

  item->next     = NULL;                                /* kill to be safe   */
  item->previous = NULL;
}
