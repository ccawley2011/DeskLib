/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Mem.MidExtend.c
    Author:  Copyright � 1993, 1995 Jason Williams and Jason Howat
    Version: 2.00 (18 Jun 1995)
    Purpose: Dynamic memory manager - reallocation
*/

#include "Desklib:Error.h"
#define __dl_mem_c
#include "MemDefs.h"

#include <string.h>

#ifdef MEM__DEBUG
#include <stdio.h>
#endif


static BOOL Mem__MidExtendNoCompact(mem_anchor *anchor, mem_header *chunk, int at, int by)
{
  int         available = chunk->realsize,
              olddatasize,
              newdatasize;
  mem_header *nextchunk = (mem_header *)((int)chunk + chunk->realsize),
             *prevchunk = (mem_header *)((int)chunk - chunk->prevrealsize),
             *newchunk = chunk;
  BOOL        now_last = (chunk == mem__lastchunk);
  char       *source,
             *destination;

  /* check space in adjoining blocks and use if available */
  if((chunk != mem__lastchunk) && (ISFREE(nextchunk)))
  {
    available += nextchunk->realsize;
    now_last = (nextchunk == mem__lastchunk);
  }

  if(((int)chunk != mem__heap) && (ISFREE(prevchunk)))
  {
    available += prevchunk->realsize;
    newchunk = prevchunk;
  }

  newdatasize = chunk->datasize + by;
  source = (char *)chunk + sizeof(mem_header);
  olddatasize = chunk->datasize;

  if(available >= CHUNKSIZE(chunk->datasize + by))
  {
    destination = (char *)((int)newchunk + sizeof(mem_header));
    *chunk->handle = destination;
    newchunk->handle = chunk->handle;
    newchunk->realsize = available;
    newchunk->datasize = newdatasize;
    mem__free -= WORDALIGN(newdatasize) - WORDALIGN(olddatasize);

    if(!now_last)
    {
      mem_header *nn = (mem_header *)((int)newchunk + available);
      nn->prevrealsize = available;
    }

    memmove(destination, source, at);
    memmove(destination + at + by, source + at, olddatasize - at);

    Mem__SplitOffFreeChunk(newchunk);
  }
  else /* try to alloc block of new size and copy old one over */
  {
    if(!Mem_Alloc((void *)&destination, newdatasize))
      return FALSE;

    memmove(destination, source, at);
    memmove(destination + at + by, source + at, olddatasize - at);

    Mem_Free(anchor);
    *anchor = destination;
    Mem__FindChunk((void *)&destination, &chunk);
    chunk->handle = anchor;
  }

  return TRUE;
}

extern BOOL Mem_MidExtend(mem_anchor *anchor, int at, int by)
/*  Enlarges or reduces a Mem chunk by moving all data beyond 'at' by
 *  'by' bytes up or down in memory. 'at' is an offset within the chunk.
 *
 *  Goes to rather a lot of effort to avoid moving the base address of
 *  this chunk and others, but if mem_autocompact allows, it will compact
 *  if it is absolutely necessary in order to manage the extension.
 *
 *  Returns TRUE if it succeeds
 */
{
  mem_header *chunk,
             *bestfit = NULL,
             *start, *end,
             *best_start = NULL, *best_end = NULL,
             *scan_start, *scan_end,
             *end_of_heap;
  int         bestfit_size = 0,
              best_move = 0, best_free,
              move_count, free_count,
              needed,
              newdatasize, extchunksize;
  char       *source,
             *destination;


  if(by == 0)         /* Zero bytes? Certainly sir! Anything else? */
    return(TRUE);

  if(at < 0 || !Mem__FindChunk(anchor, &chunk))
    return(FALSE);

  if(at > chunk->datasize)
    return(FALSE);

  source = (char *)chunk + sizeof(mem_header);

  /* ------ Reduce chunk ------ */
  if (by < 0)                            /* Reducing the size of the chunk   */
  {
    if (-by > at) by = -at;              /* Can't delete past start of chunk */

    mem__free += WORDALIGN(chunk->datasize) - WORDALIGN(chunk->datasize + by);

    memmove(source + at + by, source + at, chunk->datasize - at);
    chunk->datasize += by;               /* Shrink data area of this block   */

    Mem__SplitOffFreeChunk(chunk);       /* Return any free space for use    */
    /* The anchor has not changed */
    return(TRUE);
  }


  /* ------ Extend chunk ------ */
  if(mem_autocompact == mem_NOCOMPACT)
    return Mem__MidExtendNoCompact(anchor, chunk, at, by);
  else /*  allowed to relocate other blocks in the search for the cheapest way
        *  of creating enough space for the extension
        */
  {
    newdatasize = chunk->datasize + by;
    extchunksize = CHUNKSIZE(newdatasize);
    /* needed: is the number of free bytes required to perform the extension
               (will be a multiple of 4) */
    needed = WORDALIGN(newdatasize) - WORDALIGN(chunk->datasize);

    /* ensure there is enough space _before_ we go searching for the cheapest
     * way of using it
     */
    if(mem__free < needed)
    {
      /* extend the heap by at least (needed - mem__free) bytes */
      int extra = needed - mem__free,
          prevsize = mem__heapsize;

      mem__heapsize = Mem__HeapSize(mem__heapsize + extra + 16);
      mem__free += mem__heapsize - prevsize;
#ifdef MEM__DEBUG
fprintf(stderr, "grow heap: %8x\n", mem__heapsize - prevsize);
fflush(stderr);
#endif
      mem__lastchunk->realsize = mem__heap + mem__heapsize - (int)mem__lastchunk;

      if(mem__free < needed)
      {
        Mem__SplitOffFreeChunk(mem__lastchunk);
        Mem__ReduceSlot();
        return FALSE;     /* unable to get enough freespace to do extension */
      }
    }

    start = chunk;
    end = (mem_header *)((int)chunk + chunk->realsize);
    end_of_heap = (mem_header *)(mem__heap + mem__heapsize);

    if(start->realsize >= extchunksize)
    {
      bestfit = start;
      bestfit_size = start->realsize;
    }

    move_count = start->datasize;
    free_count = start->realsize - CHUNKSIZE(start->datasize);

    /* Scan backwards from chunk to find start of possible run of blocks */
    while((free_count < needed) && ((int)start != mem__heap))
    {
      int used;

      start = (mem_header *)((int)start - start->prevrealsize);

      if(ISFREE(start))
      {
        used = 0;

        if(((bestfit == NULL) || (bestfit_size > start->realsize)) &&
           (start->realsize >= extchunksize))
        {
          bestfit = start;
          bestfit_size = bestfit_size;
        }
      }
      else
      {
        used = CHUNKSIZE(start->datasize);
        move_count += used;
      }

      free_count += start->realsize - used;
    }

    scan_start = start;

    /* Alternately advance end/start forwards keeping track of count of bytes
       to be moved, remembering start/end points for run of blocks with
       minimum.  At the same time scan for a single free block which is big
       enough to hold the entire extended block. Check for when start == chunk
       and adjust *_count variables accordingly */
    while(1)
    {
      /* advance end and adjust *_count stats until free_count >= needed */
      while((free_count < needed) && (end < end_of_heap))
      {
        int used;

        if(ISFREE(end))
        {
          used = 0;

          if(((bestfit == NULL) || (bestfit_size > end->realsize)) &&
             (end->realsize >= extchunksize))
          {
            bestfit = end;
            bestfit_size = bestfit_size;
          }
        }
        else
        {
          used = CHUNKSIZE(end->datasize);
          move_count += used;
        }

        free_count += end->realsize - used;

        end = (mem_header *)((int)end + end->realsize);
      }

      /* check stats and copy to best_* if needed */
      if((free_count >= needed) &&
         ((best_start == NULL) || (best_move > move_count)))
      {
        best_start = start;
        best_end = end;
        best_move = move_count;
        best_free = free_count;
      }

      if(start == chunk)
        break;

      {
        int used;

        /* adjust *_count stats and advance start one block */
        if(!ISFREE(start))
        {
          used = CHUNKSIZE(start->datasize);
          move_count -= used;
        }
        else
          used = 0;
        free_count -= start->realsize - used;
      }

      start = (mem_header *)((int)start + start->realsize);

      if(start == chunk)
        move_count -= sizeof(mem_header) + at;
    }

    scan_end = end;

    /* Consider cost of moving whole block to larger free block and choose
     * cheapest option for the extension of the block.
     * NB: as we have already ensured that (mem__free >= needed), best_start
     *     must be non-NULL, as a run of blocks has to exist.
     */
    if(best_move > chunk->datasize)
    {
      /* check chunks before scan_start and after scan_end for single free
       * block that is large enough for the extended block, as it is cheaper
       * to relocate target block.
       */
      mem_header *check;

      check = (mem_header *)mem__heap;
      while(check < scan_start)
      {
        if(ISFREE(check))
        {
          if(((bestfit == NULL) || (bestfit_size > check->realsize)) &&
             (check->realsize >= extchunksize))
          {
            bestfit = check;
            bestfit_size = check->realsize;
          }
        }

        check = (mem_header *)((int)check + check->realsize);
      }

      check = scan_end;
      while(check < end_of_heap)
      {
        if(ISFREE(check))
        {
          if(((bestfit == NULL) || (bestfit_size > check->realsize)) &&
             (check->realsize >= extchunksize))
          {
            bestfit = check;
            bestfit_size = check->realsize;
          }
        }

        check = (mem_header *)((int)check + check->realsize);
      }
    }

    if((bestfit != NULL) && (best_move > chunk->datasize))
    {
      /* it is cheaper to relocate entire chunk */
#ifdef MEM__DEBUG
fprintf(stderr, "relocate: bestfit %p\n", bestfit);
fflush(stderr);
#endif

      /* copy data */
      destination = (char *)bestfit + sizeof(mem_header);
      memmove(destination, source, at);
      memmove(destination + at + by, source + at, chunk->datasize - at);

      /* update heap control structures */
      bestfit->handle = chunk->handle;
      bestfit->datasize = newdatasize;
      Mem_Free(anchor);
      *bestfit->handle = destination;
      mem__free -= extchunksize;

      Mem__SplitOffFreeChunk(bestfit);

      return(TRUE);
    }
    else
    {
      /* perform extension by:
       *   compacting region defined by best_start/best_end
       *   move data to new locations
       *   update headers of surrounding and target chunks
       */
      mem_header *newchunk;
      int         newchunksize,
                  oldchunksize;

      if(best_start < chunk)  /* must be free space available before chunk */
      {
        Mem__ShuffleDown(best_start, chunk);
        newchunk = (mem_header *)((int)chunk - chunk->prevrealsize);
      }
      else
        newchunk = chunk;
      destination = (char *)((int)newchunk + sizeof(mem_header));

      if(best_end > (mem_header *)((int)chunk + chunk->realsize))
        Mem__ShuffleUp(chunk, best_end);

      newchunksize = chunk->realsize;
      if(best_start < chunk)
        newchunksize += newchunk->realsize;

      if(extchunksize > newchunksize)  /* sanity check */
        Error_ReportFatalInternal(0, "Unexpected failure in Mem_MidExtend");

      /* update anchors/links */
      oldchunksize = chunk->datasize;
      newchunk->handle = chunk->handle;
      newchunk->datasize = newdatasize;
      newchunk->realsize = newchunksize;
      *(newchunk->handle) = destination;

      /* move data */
      memmove(destination, source, at);
      memmove(destination + at + by, source + at, oldchunksize - at);

      if(chunk != mem__lastchunk)
      {
        mem_header *next = (mem_header *)((int)newchunk + newchunksize);
        next->prevrealsize = newchunksize;
      }
      else
        mem__lastchunk = newchunk;      /* update mem__lastchunk */

      Mem__SplitOffFreeChunk(newchunk);
    }
  }

  mem__free -= needed;   /* successful allocation - update stats */

  return(TRUE);
}
