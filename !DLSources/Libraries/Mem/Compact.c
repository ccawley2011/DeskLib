/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Mem.Compact.c
    Author:  Copyright � 1993, 1994, 1995 Jason Williams and Jason Howat
    Version: 2.00 (18 Jun 1995)
    Purpose: Dynamic memory manager - heap compaction
*/


#define __dl_mem_c
#include "MemDefs.h"

extern void Mem_Compact(void)
/*  Compacts the heap, moving all freespace to the end of the heap, and then
 *  releases as much of this freespace as possible back into the WIMP freepool.
 */
{
  if (mem__free < mem__pagesize) return;   /* Don't compact if not necessary */

  /* Gather all used chunks at beginning of heap */
  Mem__ShuffleDown((mem_header *)mem__heap,
                   (mem_header *)(mem__heap + mem__heapsize));

  /* Adjust the WimpSlot to the minimum that we require, adjusting the last
   * chunk as appropriate
   */
  Mem__ReduceSlot();

  /* Update the count of free bytes in the heap */
  if(ISFREE(mem__lastchunk))
    mem__free = mem__lastchunk->realsize;
  else
    mem__free = mem__lastchunk->realsize - CHUNKSIZE(mem__lastchunk->datasize);
}
