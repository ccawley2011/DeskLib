@
@   ####             #    #     # #
@   #   #            #    #       #          The FreeWare C library for
@   #   #  ##   ###  #  # #     # ###             RISC OS machines
@   #   # #  # #     # #  #     # #  #   ___________________________________
@   #   # ####  ###  ##   #     # #  #
@   #   # #        # # #  #     # #  #    Please refer to the accompanying
@   ####   ### ####  #  # ##### # ###    documentation for conditions of use
@   ________________________________________________________________________
@
@   File    File.s.OpenClose
@   Author  Copyright � 1993, 1995 Jason Williams and Sergio Monesi
@   Version 1.02 (01 Aug 1995)
@   Purpose SWI veneers for file operations
@              open a file for read/write
@              close an open file
@              get EOF status
@              read file extent
@              read/write file position, single byte & word, multiple bytes
@   Mods    1.02 (01 Aug 1995) Sergio Monesi
@                 Added File_ReadExtent

@   NOTES   I have bundled all of these operations into a single .s/.o file
@            because typically if any of them are used, most of them are used,
@            and they are all pretty small. You can always use this source
@            file and remove the bits you don't want if you so desire.
@            By doing this, I have been able to make access to file_lasterror
@            more efficient (saving one LDR in each function)

        .include     "RegDefs.h"
        .include     "SwiNos.h"
        .include     "Macros.h"
@
        

@
@ ---------------------------------------------------------------------------
@

@ extern os_error *file_lasterror;
@ (Global variable which holds the last file error generated)
@
        .global  file_lasterror
file_lasterror:
        .word 0
@
@ ---------------------------------------------------------------------------
@
        .global File_Open
File_Open:
@
@ extern file_handle File_Open(char *filename, file_access access);
@
        STMFD   sp!, {lr}

        MOV     a3, a2     @ Swap a1 and a2 to keep a consistent C interface
        MOV     a2, a1
        MOV     a1, a3

        MOV     a3, #0

        SWI     SWI_OS_Find + XOS_Bit

        MOVVC   a2, #0                   @ No error, so reset file_lasterror
        MOVVS   a2, a1                   @ else store error pointer
        STR     a2, file_lasterror

        MOVVS   a1, #0                   @ Error - return handle = NULL

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Close
File_Close:
@
@ extern os_error *File_Close(file_handle a1);
@
        STMFD   sp!, {lr}

        MOV     a2, a1
        MOV     a1, #0

        SWI     SWI_OS_Find + XOS_Bit

        MOVVC   a1, #0                   @ No error, so reset file_lasterror
        STR     a1, file_lasterror       @ Store error condition

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_EOF
File_EOF:
@
@ extern BOOL File_EOF(file_handle a1);
@
        STMFD   sp!, {lr}

        MOV     a2, a1
        MOV     a1, #5

        SWI     SWI_OS_Args + XOS_Bit

        MOVVC   a2, #0
        MOVVS   a2, a1
        STR     a2, file_lasterror

        MOV     a1, a3             @ Return EOF flag

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Seek
File_Seek:
@
@ extern os_error *File_Seek(file_handle a1, file_position position);
@
        STMFD   sp!, {lr}

        MOV     a3, a2
        MOV     a2, a1
        MOV     a1, #1

        SWI     SWI_OS_Args + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_ReturnPos
File_ReturnPos:
@
@ extern file_position File_ReturnPos(file_handle a1);
@
        STMFD   sp!, {lr}

        MOV     a2, a1
        MOV     a1, #0

        SWI     SWI_OS_Args + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        MOV     a1, a3        @ return file position

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_ReadExtent
File_ReadExtent:
@
@ extern int File_ReadExtent(file_handle a1);
@
        STMFD   sp!, {lr}

        MOV     a2, a1
        MOV     a1, #2

        SWI     SWI_OS_Args + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        MOV     a1, a3        @ return file extent
        MOVVS	a1, #-1

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_WriteBytes
File_WriteBytes:
@
@ extern os_error *File_WriteBytes(file_handle a1, void *buffer, int numbytes);
@
        STMFD   sp!, {v1-v4, lr}

        MOV     a4, a3
        MOV     a3, a2
        MOV     a2, a1
        MOV     a1, #2

        SWI     SWI_OS_GBPB + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        LDMFD   sp!, {v1-v4, pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_ReadBytes
File_ReadBytes:
@
@ extern int File_ReadBytes(file_handle a1, char *buffer, int numbytes);
@
        STMFD   sp!, {v1-v4, lr}

        MOV     a4, a3
        MOV     a3, a2
        MOV     a2, a1
        MOV     a1, #4

        SWI     SWI_OS_GBPB + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        MOV     a1, a4               @ Return number of bytes not read

        LDMFD   sp!, {v1-v4, pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Read8
File_Read8:
@
@ extern int File_Read8(file_handle a1);
@
        STMFD   sp!, {lr}

        MOV     a2, a1
        MOV     a1, #0

        SWI     SWI_OS_BGet + XOS_Bit

        MOVVC   a2, #0
        MOVVS   a2, a1
        STR     a2, file_lasterror      @ Store error pointer or NULL

        MVNVS   a1, #0                  @ Return -1 to indicate error

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Read32
File_Read32:
@
@ extern int File_Read32(file_handle a1);
@
        STMFD   sp!, {v1-v4, lr}

        SUB     sp, sp, #4       @ Reserve 4 bytes of workspace

        MOV     a4, #4           @ Read 4 bytes
        MOV     a3, sp           @ Into space reserved on stack
        MOV     a2, a1           @ From the given file
        MOV     a1, #4

        SWI     SWI_OS_GBPB + XOS_Bit

        MOVVC   a2, #0
        MOVVS   a2, a1
        STR     a2, file_lasterror

        LDR     a1, [sp], #4     @ Return the word, restore stack pointer
        MVNVS   a1, #0           @ If error, then return -1

        LDMFD   sp!, {v1-v4, pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Read32R
File_Read32R:
@
@ extern int File_Read32R(file_handle a1);
@
        STMFD   sp!, {lr}
        BL      File_Read32                 @ Read the 32-bit value into a1
                                            @ ... and then reverse the bytes
                                            @  a1    a2    a3
                                            @ 1234
        MOV     a2, a1, LSR #24             @       xxx1
        BIC     a1, a1, #0xFF000000          @ x234
        MOV     a3, a1, LSR #16             @             xxx2
        ORR     a2, a2, a3, LSL #8          @       xx21
        AND     a3, a1, #0x000000FF          @             xxx4
        AND     a1, a1, #0x0000FF00          @ xx3x
        ORR     a2, a2, a1, LSL #8          @       x321
        ORR     a1, a2, a3, LSL #24         @ 4321
        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Write8
File_Write8:
@
@ extern os_error *File_Write8(file_handle a1, int byte);
@
        STMFD   sp!, {lr}

        MOV     a3, a2        @ Swap r0 and r1 over to retain a consistent
        MOV     a2, a1        @ C interface (handle always 1st arg)
        MOV     a1, a3

        SWI     SWI_OS_BPut + XOS_Bit

        MOVVC   a1, #0
        STR     a1, file_lasterror

        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Write32
File_Write32:
@
@ extern os_error *File_Write32(file_handle a1, int word);
@
        STMFD   sp!, {v1-v4, lr}

        SUB     sp, sp, #4       @ Reserve 4 bytes of workspace
        STR     a2, [sp]         @ Place word to write into workspace

        MOV     a4, #4           @ Write 4 bytes
        MOV     a3, sp           @ From space reserved on stack
        MOV     a2, a1           @ To the given file
        MOV     a1, #2

        SWI     SWI_OS_GBPB + XOS_Bit

        ADD     sp, sp, #4       @ restore stack pointer

        MOVVC   a1, #0
        STR     a1, file_lasterror

        LDMFD   sp!, {v1-v4, pc}
@
@ ---------------------------------------------------------------------------
@
        .global File_Write32R
File_Write32R:
@
@ extern os_error *File_Write32R(file_handle a1, int a2);
@
        STMFD   sp!, {lr}
                                            @  a2    a4    a3
                                            @ 1234
        MOV     a4, a2, LSR #24             @       xxx1
        BIC     a2, a2, #0xFF000000          @ x234
        MOV     a3, a2, LSR #16             @             xxx2
        ORR     a4, a4, a3, LSL #8          @       xx21
        AND     a3, a2, #0x000000FF          @             xxx4
        AND     a2, a2, #0x0000FF00          @ xx3x
        ORR     a4, a4, a2, LSL #8          @       x321
        ORR     a2, a4, a3, LSL #24         @ 4321

        BL      File_Write32                @ Write the word
        LDMFD   sp!, {pc}
@
@ ---------------------------------------------------------------------------
@
