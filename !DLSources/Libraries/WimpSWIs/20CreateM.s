;
;       Title                  : Wimp Create Menu.
;       System                 : Wimp Library
;       Version                : 1.0
;       Copyright              : (C) John Winters
;       Date                   : 12th January, 1990
;       Author                 : John H. Winters
;
;       Function               : Creates a menu.
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
        STARTCODE Wimp_CreateMenu
;
;        STMFD   sp!, {lr}
        MOV     ip, lr

        MOV     a4, a3
        MOV     a3, a2
        MOV     a2, a1
        SWI     SWI_Wimp_CreateMenu + XOS_Bit
        MOVVC   a1, #0

        MOVS    pc, ip
;        LDMFD   sp!, {pc}^
;
        END
