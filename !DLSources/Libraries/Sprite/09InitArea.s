;
;       Title                  : Sprite 9U
;       System                 : Sprite Library
;       Version                : 1.0
;       Copyright              : (C) John Winters
;       Date                   : 27th January, 1992
;       Author                 : John H. Winters
;
;       Function               : Issues an OS_SpriteOp 9.
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
        STARTCODE Sprite_InitArea
;
        STMFD   sp!, {lr}
        MOV     a2, a1
        MOV     a1, #256
        ADD     a1, a1, #9
        SWI     OS_SpriteOp + XOS_Bit
        MOVVC   a1, #0
        LDMFD   sp!, {pc}
;
        END
