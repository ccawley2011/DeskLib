; Author: Copyright 1993 Shaun Blackmore

        GET     ^.h.regdefs
        GET     ^.h.swinos
        GET     ^.h.macros

;os_error *Font_Converttopoints(int x, int y, int *xout, int *yout)



        PREAMBLE
        STARTCODE Font_Converttopoints
;
        STMFD   sp!, {r4,lr}
        MOV     r4,r3
        MOV     r3,r2
        MOV     r2,r1
        MOV     r1,r0
        SWI     SWI_Font_Converttopoints + XOS_Bit
        STR     r1,[r3,#0]
        STR     r2,[r4,#0]
        MOVVC   r0,#0
        LDMFD   sp!, {r4,pc}
;
        END
