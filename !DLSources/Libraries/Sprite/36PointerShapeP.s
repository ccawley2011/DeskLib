@
@       Title                  : Set Pointer Shape
@       System                 : Sprite Library
@       Version                : 1.0
@       Copyright              : (C) John Tytgat
@       Date                   : 29 Nov 2005
@       Author                 : John Tytgat
@
@       Function               : Set pointer shape
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
        
        .globl Sprite_SetPointerShapeP
@
        MOV       ip, sp
        STMFD     sp!, {a1-a3, v1-v4, lr}
        LDMFD     ip, {v3, v4}
        LDMIA     a4, {v1, v2}
	LDMFD     sp!, {a2-a4}
        MOV       a1, #512 + 36
        SWI       OS_SpriteOp + XOS_Bit
        MOVVC     a1, #0
        LDMFD     sp!, {v1-v4, pc}
@
