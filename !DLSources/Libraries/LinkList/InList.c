/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    LinkList.InList.c
    Author:  Copyright � 1992 Jason Williams
    Version: 1.02 (16 Mar 1992)
    Purpose: Linked list handling functions
*/


#include <stdlib.h>
#include <stdio.h>

#include "DeskLib:LinkList.h"

extern BOOL LinkList_InList(linklist_header *anchor, linklist_header *item)
{
  linklist_header *ptr;

  ptr = anchor->next;
  while (ptr != NULL)
  {
    if (ptr == item)                               /* compare item ADDRESSES */
      return(TRUE);

    ptr = ptr->next;
  }

  return(FALSE);
}
