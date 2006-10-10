/*
    ####             #    #     # #
    #   #            #    #       #          The FreeWare C library for
    #   #  ##   ###  #  # #     # ###             RISC OS machines
    #   # #  # #     # #  #     # #  #   ___________________________________
    #   # ####  ###  ##   #     # #  #
    #   # #        # # #  #     # #  #    Please refer to the accompanying
    ####   ### ####  #  # ##### # ###    documentation for conditions of use
    ________________________________________________________________________

    File:    Template.Clone.c
    Author:  Copyright � 1992 Jason Williams
             Thanks to John Winters for supplying the code that I hacked
             changed, hacked, rewrote, and then wrote again from scratch!
    Version: 1.11 (13 Jul 1993)
    Purpose: Loading, cacheing, and retrieval of window templates
*/


#include "TempDefs.h"



extern window_block *Template_Clone(const char *name, int maxtitlesize)
{
  template_record *t;
  window_block    *window;
  unsigned int     icon;
  icon_block      *icons;

  t = Template__FindTemplate(name);
  if (t == NULL)
    return(NULL);

  window = (window_block *) malloc(sizeof(window_block) +
                                (sizeof(icon_block) * t->windowdef->numicons));
  if (window == NULL)
    Error_ReportFatalInternal(ERR1, ERRMESS1);

  memcpy(window, t->windowdef, sizeof(window_block) +
                                (sizeof(icon_block) * t->windowdef->numicons));

  if (window->titleflags.data.indirected)
  {
    if (maxtitlesize == template_TITLEMIN)
      maxtitlesize = window->title.indirecttext.bufflen;
    else if (maxtitlesize < 1)
      maxtitlesize = 260;                         /* default ind. title size */

    window->title.indirecttext.buffer  = (char *) malloc(maxtitlesize);
    window->title.indirecttext.bufflen = maxtitlesize;
    if (window->title.indirecttext.buffer == NULL)
      Error_ReportFatalInternal(ERR1, ERRMESS1);

    strncpy(window->title.indirecttext.buffer,
            t->windowdef->title.indirecttext.buffer,
            window->title.indirecttext.bufflen-1);
    window->title.indirecttext.buffer[window->title.indirecttext.bufflen-1] =0;
  }

  icons = (icon_block *) ((int)window + sizeof(window_block));
  for (icon = 0; icon < t->windowdef->numicons; icon++)
  {
    if (icons[icon].flags.data.indirected && icons[icon].flags.data.text)
    {
      char *oldtext = icons[icon].data.indirecttext.buffer;

      icons[icon].data.indirecttext.buffer = (char *)
                                malloc(icons[icon].data.indirecttext.bufflen);
      if (icons[icon].data.indirecttext.buffer == NULL)
        Error_ReportFatalInternal(ERR1, ERRMESS1);

      strncpy(icons[icon].data.indirecttext.buffer,
              oldtext, icons[icon].data.indirecttext.bufflen - 1);
      icons[icon].data.indirecttext.buffer[
               icons[icon].data.indirecttext.bufflen - 1] = 0;

      oldtext = icons[icon].data.indirecttext.validstring;
      if ((int)oldtext > 0)
      {
        int size;

        size = strlencr(oldtext);
        icons[icon].data.indirecttext.validstring = (char *) malloc(size + 1);
        if (icons[icon].data.indirecttext.validstring == NULL)
          Error_ReportFatalInternal(ERR1, ERRMESS1);

        strncpy(icons[icon].data.indirecttext.validstring, oldtext, size);
        icons[icon].data.indirecttext.validstring[size] = 0;
      }
    }
  }

  return(window);
}
