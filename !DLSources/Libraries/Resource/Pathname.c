/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Resource.Pathname.c
    Author:  Copyright � 1993 Jason Williams
    Version: 1.00 (15 Jul 1993)
    Purpose: Global variable - Resource filename prefix string
*/

#include "DeskLib:Resource.h"


char resource_pathname[32] = "\0";      /* no path (use CSD) if user not set */
