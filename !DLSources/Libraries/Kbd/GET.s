; Author:  Copyright 1993 Jason Williams
; Version: 1.00 (24 Jul 1993)

; int Kbd_GET(void)
; (OS_ReadC veneer)
; returns the ASCII code of the next pressed (buffered) key (as in BASIC's GET)


        GET     ^.h.regdefs
        GET     ^.h.swinos
        GET     ^.h.macros


        PREAMBLE
        STARTCODE Kbd_GET

        STMFD  sp!, {lr}
        SWI    SWI_OS_ReadC + XOS_Bit
        LDMFD  sp!, {pc}^

        END
