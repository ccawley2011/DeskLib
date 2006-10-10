/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Debug1.c.heapgraph
    Author:  Julian Smith
    Version: 0.00 (04 Jun 1995)
    Purpose: Provides a set of Debug_ function which uses the
             functions in the HeapGraph library.
*/


#include <stdarg.h>
#include <stdio.h>

#undef vsprintf

#include "DeskLib:Debug.h"

#define HEAPGRAPH_DEBUG
#include "HeapGraph.Debug.h"
#undef Debug_Printf

void	Debug_Initialise( void)
{
}


int	Debug_Printf( const char *format, ...)
/* A bit tacky 'cos HeapGraph doesn't have a HeapGraph_VSendf function	*/
{
char	buffer[ 500];
va_list	va;
int	i;

va_start(va, format);
i = vsprintf( buffer, format, va);
va_end(va);

HeapGraph_Debug_Printf( buffer);

return i;
}


void	Debug_Print( const char *text)
{
HeapGraph_Debug_Printf( (char *) text);
}
