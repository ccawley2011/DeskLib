;   ####             #    #     # #
;   #   #            #    #       #          The FreeWare C library for
;   #   #  ##   ###  #  # #     # ###             RISC OS machines
;   #   # #  # #     # #  #     # #  #   ___________________________________
;   #   # ####  ###  ##   #     # #  #
;   #   # #        # # #  #     # #  #    Please refer to the accompanying
;   ####   ### ####  #  # ##### # ###    documentation for conditions of use
;   ________________________________________________________________________
;
;   File:    Module.s.07Free
;   Author:  Copyright � 1993 Jason Howat
;   Version: 1.00 (23 Nov 1993)
;   Purpose: Deallocate a block of the RMA.

        GET     RegDefs.h
        GET     swinos.h
        GET     Macros.h

; os_error *Module_Free(void *block);


        PREAMBLE
        STARTCODE Module_Free
;
        STMFD   sp!, {lr}
        MOV     a3, a1
        MOV     a1, #7
        SWI     SWI_OS_Module + XOS_Bit
        MOVVC   a1, #0
        LDMFD   sp!, {pc}
;
        END
