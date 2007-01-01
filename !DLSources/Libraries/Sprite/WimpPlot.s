@
@       Title                  : Wimp Plot
@       System                 : Sprite Library
@       Version                : 1.0
@       Copyright              : (C) Ainsley Pereira
@       Date                   : Sun 27th February 94
@       Author                 : Ainsley M. Pereira
@
@       Function               : Plots sprite in window
@
@
@       Modification history.
@
@       Version                : (Reflect in header IDENT)
@       Date                   :
@       Author                 :
@       Changes                :
@
@
@============================================================================
@
@  Include files.
@
@============================================================================
@
        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"
@
@============================================================================
@
@  Code.
@
@============================================================================
@
        
        .globl Sprite_WimpPlot
@
        MOV       ip, sp
        STMFD     sp!, {a1-a4, v1-v6, lr}
        SUB       v3, sp, #16               @ v3 -> scale block
        SUB       v4, v3, #16               @ v4 -> pix trans block
        SUB       sp, sp, #32
        MOV       a3,a2
        MOV       a2,a1
        MOV       a1,#0x100
        SWI       Wimp_ReadPixTrans + XOS_Bit
        LDR       v6, [sp, #32 +8]
        LDR       v5, [v6, #4]    @ Y
        LDR       v1, [a4, #20]   @ scroll.y
        SUB       v5, v5, v1      @ y - scroll.y
        LDR       v1, [a4, #12]   @ screenrect.max.y
        ADD       v1, v5, v1
        LDR       v5, [v6]        @ X
        LDR       v6, [a4, #16]   @ scroll.x
        SUB       v5, v5, v6      @ x - scroll.x
        LDR       v6, [a4, #0]    @ screenrect.min.x
        ADD       a4, v5, v6
        LDR       v2, [ip]
        LDR       a3, [sp, #32 +4]
        LDR       a2, [sp, #32 +0]
        MOV       a1,#256
        ADD       a1, a1, #52
        SWI       OS_SpriteOp + XOS_Bit
        ADD       sp, sp, #36
        MOVVC     a1, #0
        LDMFD     sp!, {a2-a4, v1-v6, pc}
@
