static void text_plain_flowed_handler (BODY *a, STATE *s)
{
  char line[LONG_STRING];
  char indent[LONG_STRING];

  int  quoted = -1;
  int  last_quoted;
  int  full = 1;
  int  last_full;
  int  col = 0, tmpcol;

  int  i_add = 0;
  int  add = 0;
  int  soft = 0;
  int  l, rl;
  
  int  flowed_max;
  int  bytes = a->length;
  int  actually_wrap = 0;
  
  char *cont = NULL;
  char *tail = NULL;
  char *lc = NULL;
  char *t;
  
  *indent = '\0';
  
  if (s->prefix)
    add = 1;
  
  if ((flowed_max = FLOWED_MAX) > COLS - 3)
    flowed_max = COLS - 3;
  if (flowed_max > COLS - WrapMargin)
    flowed_max = COLS - WrapMargin;
  if (flowed_max <= 0)
    flowed_max = COLS;
    

  while (bytes > 0 && fgets (line, sizeof (line), s->fpin))
  {
    bytes        -= strlen (line);
    tail          = NULL;

    last_full     = full;
    
    /* 
     * If the last line wasn't fully read, this is the
     * tail of some line. 
     */
    actually_wrap = !last_full; 
    
    if ((t = strrchr (line, '\r')) || (t = strrchr (line, '\n')))
    {
      *t   = '\0';
      full = 1;
    }
    else if ((t = strrchr (line, ' ')) || (t = strrchr (line, '\t')))
    {
      /* 
       * Bad: We have a line of more than LONG_STRING characters.
       * (Which SHOULD NOT happen, since lines SHOULD be <= 79
       * characters long.)
       * 
       * Try to simulate a soft line break at a word boundary.
       * Handle the rest of the line next time.
       * 
       * Give up when we have a single word which is longer than
       * LONG_STRING characters.  It will just be split into parts,
       * with a hard line break in between. 
       */

      full = 0;
      l    = strlen (t + 1);
      t[0] = ' ';
      t[1] = '\0';

      if (l)
      {
	fseek (s->fpin, -l, SEEK_CUR);
	bytes += l;
      }
    }
    else
      full = 0;

    last_quoted = quoted;

    if (last_full)
    {
      /* 
       * We are in the beginning of a new line. Determine quote level
       * and indentation prefix 
       */
      for (quoted = 0; line[quoted] == '>'; quoted++)
	;
      
      cont = line + quoted;
      
      /* undo space stuffing */
      if (*cont == ' ')
	cont++;

      /* If there is an indentation, record it. */
      cont  = flowed_skip_indent (indent, cont);
      i_add = flowed_visual_strlen (indent, quoted + add);
    }
    else
    {
      /* 
       * This is just the tail of some over-long line. Keep
       * indentation and quote levels.  Don't unstuff.
       */
      cont = line;
    }

    /* If we have a change in quoting depth, wrap. */

    if (col && last_quoted != quoted && last_quoted >= 0)
    {
      state_putc ('\n', s);
      col = 0;
    }
    
    do 
    {
      if (tail)
	cont = tail;

      SKIPWS (cont);
      
      tail = NULL;
      soft = 0;
      
      /* try to find a point for word wrapping */

    retry_wrap:
      l  = flowed_visual_strlen (cont, quoted + i_add + add + col);
      rl = mutt_strlen (cont);
      if (quoted + i_add + add + col + l > flowed_max)
      {
	actually_wrap = 1;

	for (tmpcol = quoted + i_add + add + col, t = cont;
	     *t && tmpcol < flowed_max; t++)
	{
	  if (*t == ' ' || *t == '\t')
	    tail = t;
	  if (*t == '\t')
	    tmpcol = (tmpcol & ~7) + 8;
	  else
	    tmpcol++;
	}
	
	if (tail)
	{
	  *tail++ = '\0';
	  soft = 2;
	}
      }

      /* We seem to be desperate.  Get me a new line, and retry. */
      if (!tail && (quoted + add + col + i_add + l > flowed_max) && col)
      {
	state_putc ('\n', s);
	col = 0;
	goto retry_wrap;
      }

      /* Detect soft line breaks. */
      if (!soft && ascii_strcmp (cont, "-- "))
      {
	lc = strrchr (cont, ' ');
	if (lc && lc[1] == '\0')
	  soft = 1;
      }

      /* 
       * If we are in the beginning of an output line, do quoting
       * and stuffing. 
       * 
       * We have to temporarily assemble the line since display
       * stuffing (i.e., turning off quote coloring) may depend on
       * the line's actual content.  You never know what people put
       * into their regular expressions. 
       */
      if (!col)
      {
	char tmp[LONG_STRING];
	snprintf (tmp, sizeof (tmp), "%s%s", indent, cont);

	flowed_quote (s, quoted);
	flowed_stuff (s, tmp, quoted + add);

	state_puts (indent, s);
      }

      /* output the text */
      state_puts (cont, s);
      col += flowed_visual_strlen (cont, quoted + i_add + add + col);
      
      /* possibly indicate a soft line break */
      if (soft == 2)
      {
	state_putc (' ', s);
	col++;
      }
      
      /* 
       * Wrap if this display line corresponds to a 
       * text line. Don't wrap if we changed the line.
       */
      if (!soft || (!actually_wrap && full))
      {
	state_putc ('\n', s);
	col = 0;
      }
    }
    while (tail);
  }

  if (col)
    state_putc ('\n', s);
  
}