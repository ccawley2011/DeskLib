@   ####             #    #     # #
@   #   #            #    #       #          The FreeWare C library for
@   #   #  ##   ###  #  # #     # ###             RISC OS machines
@   #   # #  # #     # #  #     # #  #   ___________________________________
@   #   # ####  ###  ##   #     # #  #
@   #   # #        # # #  #     # #  #    Please refer to the accompanying
@   ####   ### ####  #  # ##### # ###    documentation for conditions of use
@   ________________________________________________________________________
@
@   File    Str.strcatcr.s
@   Author  Copyright � 1994 Jason Williams
@   Version 2.00 (24 Sep 1994)
@   Purpose Concatenate two CR/NUL terminated strings - note that this will
@            change the terminator of the result to a NUL (0).


        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

        
        .global strcatcr
strcatcr:
@    extern char *strcatcr(char *s1, const char *s2);


        SUB       a3, a1, #1         @ a3 = pre-incrementing ptr to dest
strcat_findend:
        LDRB      ip, [a3, #1]!      @ scan for the terminating char in dest
        CMP       ip, #31
        BGT       strcat_findend

strcat_copy:
        LDRB      ip, [a2], #1      @ a2 = post-incrementing  ptr to source
        CMP       ip, #31
        STRHIB    ip, [a3], #1      @ if char > 31, append to dest
        BGT       strcat_copy       @   and loop

        MOV       ip, #0            @ NULL terminate
        STRB      ip, [a3]

        MOV       pc, lr            @ return(a1) (ptr to source)

@ ---
@ Old code (by Ainsley Pereira)
@
@        STMFD     sp!,{v1,v2,lr}
@        MOV       v1,#0
@        MOV       v2,#0
@strcatcr_00
@        LDRB      ip,[a1,v1]
@        CMP       ip,#31
@        ADDGT     v1,v1,#1
@        BGT       strcatcr_00
@strcatcr_01
@        LDRB      ip,[a2,v2]
@        CMP       ip,#31
@        STRBGT    ip,[a1,v1]
@        ADDGT     v1,v1,#1
@        ADDGT     v2,v2,#1
@        BGT       strcatcr_01
@        MOV       ip,#0
@        STRB      ip,[a1,v1]
@        LDMFD     sp!, {v1,v2, pc}^
@

