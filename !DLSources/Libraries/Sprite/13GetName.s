;
;       Title                  : Get Name
;       System                 : Sprite Library
;       Version                : 1.0
;       Copyright              : (C) Ainsley Pereira
;       Date                   : Sun 27th February 94
;       Author                 : Ainsley M. Pereira
;
;       Function               : Gets sprite name
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
        GET     ^.h.regdefs
        GET     ^.h.swinos
        GET     ^.h.macros
;
;============================================================================
;
;  Code.
;
;============================================================================
;
        PREAMBLE
        STARTCODE Sprite_GetName
;
        STMFD     sp!, {v1,lr}
        MOV       v1, a3
        MOV       a4, #13
        MOV       a3, a2
        MOV       a2, a1
        MOV       a1, #256
        ADD       a1, a1, #13
        SWI       OS_SpriteOp + XOS_Bit
        MOV       a1, a4
        MOVVS     a1, #0
        LDMFD     sp!, {v1,pc}
;
	END
