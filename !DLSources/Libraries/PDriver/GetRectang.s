;   ####             #    #     # #
;   #   #            #    #       #          The FreeWare C library for
;   #   #  ##   ###  #  # #     # ###             RISC OS machines
;   #   # #  # #     # #  #     # #  #   ___________________________________
;   #   # ####  ###  ##   #     # #  #
;   #   # #        # # #  #     # #  #    Please refer to the accompanying
;   ####   ### ####  #  # ##### # ###    documentation for conditions of use
;   ________________________________________________________________________
;
;   File:    PDriver.GetRectang.s
;   Author:  Copyright � 1993 Jason Howat
;   Version: 1.00 (07 Jul 1993)
;   Purpose: Get the next print rectangle.

        GET     ^.h.regdefs
        GET     ^.h.swinos
        GET     ^.h.macros

; os_error *PDriver_GetRectangle(wimp_rect *rectangle_to_print, int *finished, int *rectangle_id);

        PREAMBLE
        STARTCODE PDriver_GetRectangle
;
        STMFD   sp!, {v1,lr}
        MOV     a4, a2
        MOV     v1, a3
        MOV     a2, a1
        SWI     SWI_PDriver_GetRectangle + XOS_Bit
        LDMVSFD sp!, {v1,pc}
        CMP     a4, #0
        STRNE   r0, [a4, #0]
        CMP     v1, #0
        STRNE   r2, [v1, #0]
        MOV     a1, #0
        LDMFD   sp!, {v1,pc}
;
        END
