@   ####             #    #     # #
@   #   #            #    #       #          The FreeWare C library for
@   #   #  ##   ###  #  # #     # ###             RISC OS machines
@   #   # #  # #     # #  #     # #  #   ___________________________________
@   #   # ####  ###  ##   #     # #  #
@   #   # #        # # #  #     # #  #    Please refer to the accompanying
@   ####   ### ####  #  # ##### # ###    documentation for conditions of use
@   ________________________________________________________________________
@
@   File    Serial.s.GetRxRate
@   Author  Copyright � 1993 Jason Howat
@   Version 1.00 (21 Nov 1993)
@   Purpose Read the baud rate of data received on the serial line.

        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

@ serial_rate Serial_GetRxRate(void);

        
        .globl Serial_GetRxRate
@
        STMFD   sp!, {lr}
        MOV     a1, #5
        MVN     a2, #0
        SWI     SWI_OS_SerialOp + XOS_Bit
        MOV     a1, a2
        LDMFD   sp!, {pc}
@
