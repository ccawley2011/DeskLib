;
;       Title                  : Read pixel
;       System                 : Sprite Library
;       Version                : 1.0
;       Copyright              : (C) Ainsley Pereira
;       Date                   : Sun 27th February 94
;       Author                 : Ainsley M. Pereira
;
;       Function               : Read pixel from a sprite
;
;
;       Modification history.
;
;       Version                : (Reflect in header IDENT)
;       Date                   :
;       Author                 :
;       Changes                :
;
;
;============================================================================
;
;  Include files.
;
;============================================================================
;
        GET     RegDefs.h
        GET     swinos.h
        GET     Macros.h
;
;============================================================================
;
;  Code.
;
;============================================================================
;
        PREAMBLE
        STARTCODE Sprite_ReadPixel
;
        STMFD     sp!, {a4, v1-v6, lr}
        LDR       a4,[a3, #0]
        LDR       v1,[a3, #4]
        MOV       a3,a2
        MOV       a2,a1
        MOV       a1, #256
        ADD	  a1, a1, #41
        SWI       OS_SpriteOp + XOS_Bit
        LDMFD     sp!, {a1}
        CMP       a1,#0
        STRNE     v3,[a1]
        MOV       a1,v2
        MVNVS     a1,#0
        LDMFD     sp!, {v1-v6, pc}
;
	END
