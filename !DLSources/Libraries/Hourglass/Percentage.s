@   ####             #    #     # #
@   #   #            #    #       #          The FreeWare C library for
@   #   #  ##   ###  #  # #     # ###             RISC OS machines
@   #   # #  # #     # #  #     # #  #   ___________________________________
@   #   # ####  ###  ##   #     # #  #
@   #   # #        # # #  #     # #  #    Please refer to the accompanying
@   ####   ### ####  #  # ##### # ###    documentation for conditions of use
@   ________________________________________________________________________
@
@   File    Hourglass.s.Percentage
@   Author  Copyright � 1993 Jason Howat
@   Version 1.00 (24 Jul 1993)
@   Purpose Alter the percentage displayed under the hourglass

        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

@ void Hourglass_Percentage(int percent);

        
        .globl Hourglass_Percentage
@
        STMFD   sp!, {lr}
        SWI     SWI_Hourglass_Percentage + XOS_Bit
        LDMFD   sp!, {pc}
@
