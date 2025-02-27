/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    File.LoadTo.c
    Author:  Copyright � 1994 Peter Gaunt
    Version: 1.00 (12 Mar 1994)
    Purpose: Loads a file at a given address.
*/

#include "kernel.h"

#include "DeskLib:Core.h"
#include "DeskLib:SWI.h"
#include "DeskLib:File.h"
/*
 * Loads a file at an address
 *
 * If size is not NULL then it is set to file size (except on error).
 *
 * Returns NULL or pointer to error.
 */

extern os_error *File_LoadTo(const char *filename, void *address, int *size)
{
  _kernel_swi_regs r;
  _kernel_oserror  *error;

  r.r[0] = 255;
  r.r[1] = (int) filename;
  r.r[2] = (int) address;
  r.r[3] = 0;

  error = _kernel_swi( SWI_OS_File, &r, &r );

  if (error != NULL)
    return( (os_error *) error );

  if (size != NULL)
    *size = r.r[4];

  return( NULL );

}
