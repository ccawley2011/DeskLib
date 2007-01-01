@
@       Title                  : Read palette size
@       System                 : Sprite Library
@       Version                : 1.0
@       Copyright              : (C) Ainsley Pereira
@       Date                   : Sun 27th February 94
@       Author                 : Ainsley M. Pereira
@
@       Function               : Reads size of sprite's palette
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
        
        .globl Sprite_ReadPaletteSize
@
        STMFD     sp!, {a1-a2, v1-v2, lr}
        LDMFD     sp!, {a2-a3}
        MOV       a1, #256
        ADD       a1, a1, #37
        MVN       a4, #0
        SWI       OS_SpriteOp + XOS_Bit
        MOVVC     a1, a4
        MOVVS     a1, #0
        LDMFD     sp!, {v1-v2, pc}
@
