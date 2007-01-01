@   ####             #    #     # #
@   #   #            #    #       #          The FreeWare C library for
@   #   #  ##   ###  #  # #     # ###             RISC OS machines
@   #   # #  # #     # #  #     # #  #   ___________________________________
@   #   # ####  ###  ##   #     # #  #
@   #   # #        # # #  #     # #  #    Please refer to the accompanying
@   ####   ### ####  #  # ##### # ###    documentation for conditions of use
@   ________________________________________________________________________
@
@   File    Filing.s.SingleFul2
@   Author  Copyright � 1994, 1995 Sergio Monesi
@   Version 1.01 (6 Jun 1995)
@   Purpose Reads a single directory entry (full version)
@   Mods    6 June 1995 - changed procedure name to a more
@                          DeskLib-compliant style

        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

@ os_error *Filing_SingleFullDirEntry2(char *dirname, void *buf,
@                                      int size, char *filename);

        
        .globl Filing_SingleFullDirEntry2
@
        STMFD   sp!, {r4-r6,lr}
        MOV     r6, r3
        MOV     r5, r2
        MOV     r4, #0
        MOV     r2, r1
        MOV     r1, r0
        MOV     r0, #11

loop:
        MOV     r3, #256
        SWI     SWI_OS_GBPB + XOS_Bit
        LDMVSFD sp!, {r4-r6,pc}

        TEQ     r3, #1
        BEQ     endok
        TEQ     r4, #0
        BGE     loop

        MOV     r0, #0                 @
        STR     r0, [r2, #16]          @ objtype = 0
        LDMFD   sp!, {r4-r6,pc}

endok:
        MOV     r0, #0
        LDMFD   sp!, {r4-r6,pc}
@
