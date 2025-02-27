/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    File.printf.c
    Author:  Copyright � 1994 Jason Howat
    Version: 1.00 (28 May 1994)
             1.01 (04 Sep 2007) Changed vsprintf to vsnprintf
    Purpose: Do a "printf" to a File.
*/

#include <stdarg.h>
#include <stdio.h>

/* commented out 5/9/07 - not sure why #undef was here?
#undef vsprintf
*/

#include "DeskLib:File.h"

extern int File_printf(file_handle file, const char *format, ...)
{
  va_list argp;
  char    buff[512];
  int     byteswritten;

  va_start(argp,format);
  byteswritten = vsnprintf(buff, sizeof(buff), format, argp);
  if(byteswritten > 0)
    File_WriteBytes(file, buff, byteswritten);
  va_end(argp);

  return byteswritten;
}
