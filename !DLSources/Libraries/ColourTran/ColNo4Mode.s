;-------------------------------------------------------------------------------
; int ColourTrans_ReturnColourNumberForMode(int pal_entry, int mode, int pal);
; Copyright 1993 Jason Howat


        GET     macros.h
        GET     regdefs.h
        GET     swinos.h
;
        PREAMBLE
        STARTCODE ColourTrans_ReturnColourNumberForMode
;
        STMFD   sp!,{lr}
        SWI     SWI_ColourTrans_ReturnColourNumberForMode + XOS_Bit
        MOVVS   r0, #-1
        LDMFD   sp!,{pc}
;
        END
