;   ####             #    #     # #
;   #   #            #    #       #          The FreeWare C library for
;   #   #  ##   ###  #  # #     # ###             RISC OS machines
;   #   # #  # #     # #  #     # #  #   ___________________________________
;   #   # ####  ###  ##   #     # #  #
;   #   # #        # # #  #     # #  #    Please refer to the accompanying
;   ####   ### ####  #  # ##### # ###    documentation for conditions of use
;   ________________________________________________________________________
;
;   File:    PDriver.ScreenDump.s
;   Author:  Copyright � 1993 Jason Howat
;   Version: 1.00 (07 Jul 1993)
;   Purpose: Output a screen dump to the printer.

        GET     ^.h.regdefs
        GET     ^.h.swinos
        GET     ^.h.macros

; os_error *PDriver_ScreenDump(print_job job);

        PREAMBLE
        STARTCODE PDriver_ScreenDump
;
        STMFD   sp!, {lr}
        SWI     SWI_PDriver_ScreenDump + XOS_Bit
        MOVVC   a1, #0
        LDMFD   sp!, {pc}
;
        END
