@ Copyright 1993 Shaun Blackmore and Jason Williams
@ (Shaun wrote the C version, plus the basis of this assembler, which I then
@  got working correctly and added the CMOS check into)
@ version 1.01
@
@ Interestingly, this code is only about 4 instructions shorter than its
@ C code equivalent.
@
@ Updates
@ 1.01 JW  Fixed this code so it now works under RISC OS 2. Took me ages to
@          find out that it was passing 0xffffffff instead of 0x7fffffff into
@          wimp_dragbox (that works under RO3 but not under RO2!)
@          (that meant the dragbox was limited to a rectangle between -1 and 0
@          rather than to the entire screen extent)


        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"

@ void DragASprite_DragIcon(window_handle window, icon_handle icon);

        
        .global DragASprite_DragIcon
DragASprite_DragIcon:
@
        STMFD   sp!, {r4,r5,r6,r7,lr}
        MOV     ip,sp

        SUB     sp, sp, #40        @ Set up block for GetWindowState
        STR     r0, [sp, #0]       @ icon.window=r0

        MOV     r7, r1             @ remember icon number for later...
          MOV     r1, sp           @ r1 = pointer to windowstate block

          SWI     SWI_Wimp_GetWindowState + XOS_Bit
          BVS     Exit

          LDR     r2, [sp, #4]
          LDR     r3, [sp, #20]
          SUB     r2, r2, r3       @ r2 = window_origin_x

          LDR     r3, [sp, #16]
          LDR     r4, [sp, #24]
          SUB     r3, r3, r4       @ r3 = window_origin_y

                                   @ Set up a DragBox structure
          SUB     sp, sp, #40      @ Drag Structure

          STR     r0, [sp, #0]     @ drag.window=r0
          MOV     r0, #5
          STR     r0, [sp, #4]     @ drag.type=5;

                                   @ Now get the icon state
        STR     r7, [r1, #4]       @ store icon- Block already has windowhandle
        SWI     SWI_Wimp_GetIconState + XOS_Bit
        BVS     Exit

        ADD     r1, r1, #8         @ r1 = icon block
                                   @ sp = drag structure
        LDMIA   r1,{r4,r5,r6,r7}   @ Read icon bounding rectangle

          ADD     r4, r4, r2       @ Convert offsets from window origin (TL)
          ADD     r5, r5, r3       @ into absolute screen coordinates, using
          ADD     r6, r6, r2       @ the window origin calculated above (r2,r3)
          ADD     r7, r7, r3

        ADD     r2, sp, #8         @ r1 = bounding box
        STMIA   r2,{r4,r5,r6,r7}

        MOV     r0,#0
        STR     r0,[sp,#24]        @ parent.x0 = 0
        STR     r0,[sp,#28]        @ parent.y0 = 0

        LDR     r0, VeryBig
        STR     r0,[sp,#32]        @ parent.x1 = 0x7FFFFFFF
        STR     r0,[sp,#36]        @ parent.y1 = 0x7FFFFFFF

        MOV     r7, r1             @ r7 = pointer to icon state data

                                   @ Check if DragASprite is available
        ADD     r1, pc, #DragString-.-8
        SWI     SWI_OS_SWINumberFromString + XOS_Bit
        BVS     NoDrag             @ It isn't, so do Wimp_DragBox

        MOV     r0, #161           @ Check the DragASpr configuration bit
        MOV     r1, #28
        SWI     SWI_OS_Byte + XOS_Bit
        TST     r2, #2             @ Is DragASprite enabled?
        BEQ     NoDrag             @ No - do a Wimp_DragBox

        LDR     r0, [r7, #16]      @ check for icon type - is it indirected?
        TST     r0, #256
                                   @ Not Indirected
        MOVEQ   r1, #1             @   System area
        ADDEQ   r2, r7, #20        @   Point to data

        LDRNE   r1, [r7, #24]      @ Is Indirected
        LDRNE   r2, [r7, #20]      @

        ADD     r3, sp, #8         @ r3 => Bounding box
        ADD     r4, sp, #24        @ r4 => Parent box (not actually needed)

        MOV     r0, #197           @ Flags- centered, bbox = screen bounds,
                                   @ bbox limits mouse pointer, has drop shadow

        SWI     SWI_DragASprite_Start + XOS_Bit
        B       Exit

NoDrag:
        MOV     r1, sp             @ Can't DragASprite, so Wimp_DragBox instead
        SWI     SWI_Wimp_DragBox + XOS_Bit

Exit:
        MOV     sp, ip             @ restore old stack pointer
        MOVVC   r0, #0
        LDMFD   sp!, {r4,r5,r6,r7,pc}
@
VeryBig:
        .word     0x7fffffff
@
DragString:
        .asciz     "DragASprite_Start"

