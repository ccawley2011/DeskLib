;
;       Title                  : Wimp Remove Messages.
;       System                 : Wimp Library
;       Version                : 1.0
;       Copyright              : (C) Antony Sidwell
;       Date                   : 15th January, 2002
;       Author                 : Antony Sidwell
;
;       Function               : Removes messages from the set of user messages
;                                that the Wimp sends to the task.
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
        STARTCODE Wimp_RemoveMessages
;
        MOV     ip, lr

        SWI     SWI_Wimp_RemoveMessages + XOS_Bit
        MOVVC   a1, #0

        MOV     pc, ip
;
        END
