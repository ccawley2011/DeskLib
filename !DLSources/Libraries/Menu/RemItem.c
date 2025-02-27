/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Menu.RemItem.c
    Author:  Copyright � 1993 Mark H. Wilkinson, 1994 Tony Houghton
    Version: 1.01 (24 Sep 1994)
    Purpose: Removes an item from an existing menu.
    Mods:    If first item indicates indirected title, update its replacement
*/


#include "DeskLib:Wimp.h"
#include "DeskLib:Menu.h"


void Menu_RemoveItem(menu_ptr menu, int entry)
{
  menu_item *item = (menu_item *)(((int)menu) + sizeof(menu_block));

  if (item->menuflags.data.last)
    return;
  if (entry == 0 && item->menuflags.data.indtitle && !item->menuflags.data.last)
    item[1].menuflags.data.indtitle = 1;
  while (entry > 0) {
    if (item->menuflags.data.last)
      return;
    --entry;
    ++item;
  }
  if (item->menuflags.data.last)
    item[-1].menuflags.data.last = 1;
  else
    do {
      *item = *(item+1);
    } while (item++->menuflags.data.last == 0);
}
