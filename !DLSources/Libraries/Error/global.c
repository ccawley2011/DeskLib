/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Error.global.c
    Author:  Copyright � 1994 Sergio Monesi, Julian Smith
    Version: 1.01 (06 Jun 1995)
    Purpose: Just the error_global variable!
    Mods:    06 Jun 1995 JS - changed name to error_global, and added DLL veneer.
*/

#include "DeskLib:Error.h"

os_error error_global;

#ifdef _DLL
os_error *Error__Ref_global( void) { return &error_global; }
#endif
