@ Author Copyright 1993 Shaun Blackmore

        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

@os_error *Font_StringWidth(FontString *string);

@       r0=pointer to definition block

@       [r0,#0]  = char *s string
@       [r0,#4]  = x
@       [r0,#8]  = y
@       [r0,#12] = split
@       [r0,#16] = index

        
        .globl Font_StringWidth
@
        STMFD   sp!, {r4,r5,r6,lr}
        MOV     r6,r0
        LDMIA   r6,{r1,r2,r3,r4,r5}
        SWI     SWI_Font_StringWidth + XOS_Bit
        STMIA   r6,{r1,r2,r3,r4,r5}
        MOVVC   r0,#0
        LDMFD   sp!, {r4,r5,r6,pc}
@
