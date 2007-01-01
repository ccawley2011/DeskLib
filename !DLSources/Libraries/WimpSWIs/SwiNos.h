
.equ	XOS_Bit, 0x020000

.equ	SWI_Wimp_Initialise, 0x0400c0
.equ	SWI_Wimp_CreateWindow, 0x0400c1
.equ	SWI_Wimp_CreateIcon, 0x0400c2
.equ	SWI_Wimp_DeleteWindow, 0x0400c3
.equ	SWI_Wimp_DeleteIcon, 0x0400c4
.equ	SWI_Wimp_OpenWindow, 0x0400c5
.equ	SWI_Wimp_CloseWindow, 0x0400c6
.equ	SWI_Wimp_Poll, 0x0400c7
.equ	SWI_Wimp_RedrawWindow, 0x0400c8
.equ	SWI_Wimp_UpdateWindow, 0x0400c9
.equ	SWI_Wimp_GetRectangle, 0x0400ca
.equ	SWI_Wimp_GetWindowState, 0x0400cb
.equ	SWI_Wimp_GetWindowInfo, 0x0400cc
.equ	SWI_Wimp_SetIconState, 0x0400cd
.equ	SWI_Wimp_GetIconState, 0x0400ce
.equ	SWI_Wimp_GetPointerInfo, 0x0400cf
.equ	SWI_Wimp_DragBox, 0x0400d0
.equ	SWI_Wimp_ForceRedraw, 0x0400d1
.equ	SWI_Wimp_SetCaretPosition, 0x0400d2
.equ	SWI_Wimp_GetCaretPosition, 0x0400d3
.equ	SWI_Wimp_CreateMenu, 0x0400d4
.equ	SWI_Wimp_DecodeMenu, 0x0400d5
.equ	SWI_Wimp_WhichIcon, 0x0400d6
.equ	SWI_Wimp_SetExtent, 0x0400d7
.equ	SWI_Wimp_SetPointerShape, 0x0400d8
.equ	SWI_Wimp_OpenTemplate, 0x0400d9
.equ	SWI_Wimp_CloseTemplate, 0x0400da
.equ	SWI_Wimp_LoadTemplate, 0x0400db
.equ	SWI_Wimp_ProcessKey, 0x0400dc
.equ	SWI_Wimp_CloseDown, 0x0400dd
.equ	SWI_Wimp_StartTask, 0x0400de
.equ	SWI_Wimp_ReportError, 0x0400df
.equ	SWI_Wimp_GetWindowOutline, 0x0400e0
.equ	SWI_Wimp_PollIdle, 0x0400e1
.equ	SWI_Wimp_PlotIcon, 0x0400e2
.equ	SWI_Wimp_SetMode, 0x0400e3
.equ	SWI_Wimp_SetPalette, 0x0400e4
.equ	SWI_Wimp_ReadPalette, 0x0400e5
.equ	SWI_Wimp_SetColour, 0x0400e6
.equ	SWI_Wimp_SendMessage, 0x0400e7
.equ	SWI_Wimp_CreateSubMenu, 0x0400e8
.equ	SWI_Wimp_SpriteOp, 0x0400e9
.equ	SWI_Wimp_BaseOfSprites, 0x0400ea
.equ	SWI_Wimp_BlockCopy, 0x0400eb
.equ	SWI_Wimp_SlotSize, 0x0400ec
.equ	SWI_Wimp_ReadPixTrans, 0x0400ed
.equ	SWI_Wimp_ClaimFreeMemory, 0x0400ee
.equ	SWI_Wimp_CommandWindow, 0x0400ef
.equ	SWI_Wimp_TextColour, 0x0400f0
.equ	SWI_Wimp_TransferBlock, 0x0400f1
.equ	SWI_Wimp_ReadSysInfo, 0x0400f2
.equ	SWI_Wimp_SetFontColours, 0x0400f3
.equ	SWI_Wimp_AddMessages, 0x0400f6
.equ	SWI_Wimp_RemoveMessages, 0x0400f7
.equ	SWI_Wimp_Extend, 0x0400fb

.equ	SWI_Wimp_BorderIcon, 0x081680
.equ	SWI_Wimp_BorderWindow, 0x081681
.equ	SWI_Wimp_ClaimInterface, 0x081682
.equ	SWI_Wimp_ReleaseInterface, 0x081683
.equ	SWI_Wimp_SetWorkAreaPointer, 0x081684
.equ	SWI_Wimp_RemoveWorkAreaPointer, 0x081685
.equ	SWI_Wimp_PollPointer, 0x081686
.equ	SWI_Wimp_SendHelp, 0x081687

