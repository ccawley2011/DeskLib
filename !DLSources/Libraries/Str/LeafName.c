/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Misc.Leafname.c
    Author:  Copyright � 1994 Erik de Kort
    Version: 1.01 (26 Jun 1994)
    Purpose: Determine the leaf-name of a file given a legal pathname
    Mods:    12 Jul 1995 - JPS - Changed name to Str_LeafName.
*/


#include "DeskLib:Str.h"


/* Str_LeafName() ----------------------------------------------------------
 * Return a pointer to the leaf of 'FullPath'.
 * Note that this pointer is within the 'FullPath' string.
 * If no separator (dot or colon) is encountered in FullPath, then the
 * pointer FullPath is returned.
 *
 * It is assumed that if any colons appear, then you either have a proper
 * pathname (SCSI::...) in which case a dot will appear before the leafname,
 * or you're using a path MyPath:FileName, so : is treated the same as .
 */

extern char *Str_LeafName(const char *path)
{
  char *leaf = (char *)(int)path, ch = '.';

  do
  {
    if (ch == '.' || ch == ':')
      leaf =  (char *)(int)path;
  }
  while ( (ch = *(path++)) != '\0') ;

  return leaf;
}
