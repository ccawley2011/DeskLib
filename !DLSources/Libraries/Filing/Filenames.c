/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Filing.Filenames.c
    Author:  Copyright � 1994, 1995 Sergio Monesi
    Version: 1.01 (6 Jun 1995)
    Purpose: Finds pathnames and leafnames
    Mods:    6 June 1995 - changed procedure names to a more
                           DeskLib-compliant style
             5 September 2007 - changed strcpy to strncpy
*/

#include <string.h>

#include "DeskLib:Core.h"
#include "DeskLib:Filing.h"

char *Filing_GetPathname(const char *filename, char *pathname)
{
 if (pathname==NULL || filename==NULL)
   return NULL;
 else {
   char *p;
   strncpy(pathname,filename, sizeof(pathname)-1);
   pathname[sizeof(pathname)-1] = '\0';
   p=strrchr(pathname,'.');
   if (p)
     *p=0;
   else
     *pathname=0;
   return pathname;
 }
}

char *Filing_GetLeafname(const char *filename, char *leafname)
{
 if (leafname==NULL || filename==NULL)
   return NULL;
 else {
   char *p=strrchr(filename,'.');
   strncpy(leafname,p?p+1:filename, sizeof(leafname)-1);
   leafname[sizeof(leafname)-1] = '\0';
   return leafname;
 }
}

char *Filing_FindLeafname(const char *filename)
{
 if (filename==NULL)
   return NULL;
 else {
   char *p=strrchr(filename,'.');
   return (p ? p+1 : (char *)(int)filename);
 }
}

