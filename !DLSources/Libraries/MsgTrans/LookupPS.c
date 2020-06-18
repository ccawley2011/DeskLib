/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    MsgTrans.LookupPS.c
    Author:  Copyright � 1994 Tony Houghton
    Version: 1.01 (05 Nov 1994)
    Purpose: Match a token in a Messages file
*/

#include "DeskLib:MsgTrans.h"

os_error *MsgTrans_LookupPS(msgtrans_filedesc *filedesc,
                            const char *token,
                            char *buffer, int bufflen,
                            const char *p0,
                            const char *p1,
                            const char *p2,
                            const char *p3)
{
  os_error *swierr;

  swierr = MessageTrans_Lookup(filedesc, token, &buffer, &bufflen,
                               p0, p1, p2, p3);
  if (swierr)
    return (swierr);

  /* NULL-terminate string */
  buffer[bufflen - 1] = '\0';

  return NULL;
}
