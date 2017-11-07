void text_enriched_handler (BODY *a, STATE *s)
{
  enum {
    TEXT, LANGLE, TAG, BOGUS_TAG, NEWLINE, ST_EOF, DONE
  } state = TEXT;

  long bytes = a->length;
  struct enriched_state stte;
  int c = 0;
  int tag_len = 0;
  char tag[LONG_STRING + 1];

  memset (&stte, 0, sizeof (stte));
  stte.s = s;
  stte.WrapMargin = ((s->flags & M_DISPLAY) ? (COLS-4) : ((COLS-4)<72)?(COLS-4):72);
  stte.line_max = stte.WrapMargin * 4;
  stte.line = (char *) safe_calloc (1, stte.line_max + 1);
  stte.param = (char *) safe_calloc (1, STRING);

  stte.param_len = STRING;
  stte.param_used = 0;

  if (s->prefix)
  {
    state_puts (s->prefix, s);
    stte.indent_len += mutt_strlen (s->prefix);
  }

  while (state != DONE)
  {
    if (state != ST_EOF)
    {
      if (!bytes || (c = fgetc (s->fpin)) == EOF)
	state = ST_EOF;
      else
	bytes--;
    }

    switch (state)
    {
      case TEXT :
	switch (c)
	{
	  case '<' :
	    state = LANGLE;
	    break;

	  case '\n' :
	    if (stte.tag_level[RICH_NOFILL])
	    {
	      enriched_flush (&stte, 1);
	    }
	    else 
	    {
	      enriched_putc (' ', &stte);
	      state = NEWLINE;
	    }
	    break;

	  default:
	    enriched_putc (c, &stte);
	}
	break;

      case LANGLE :
	if (c == '<')
	{
	  enriched_putc (c, &stte);
	  state = TEXT;
	  break;
	}
	else
	{
	  tag_len = 0;
	  state = TAG;
	}
	/* Yes, fall through (it wasn't a <<, so this char is first in TAG) */
      case TAG :
	if (c == '>')
	{
	  tag[tag_len] = '\0';
	  enriched_set_flags (tag, &stte);
	  state = TEXT;
	}
	else if (tag_len < LONG_STRING)  /* ignore overly long tags */
	  tag[tag_len++] = c;
	else
	  state = BOGUS_TAG;
	break;

      case BOGUS_TAG :
	if (c == '>')
	  state = TEXT;
	break;

      case NEWLINE :
	if (c == '\n')
	  enriched_flush (&stte, 1);
	else
	{
	  ungetc (c, s->fpin);
	  bytes++;
	  state = TEXT;
	}
	break;

      case ST_EOF :
	enriched_putc ('\0', &stte);
        enriched_flush (&stte, 1);
	state = DONE;
	break;

      case DONE: /* not reached, but gcc complains if this is absent */
	break;
    }
  }

  state_putc ('\n', s); /* add a final newline */

  FREE (&(stte.buffer));
  FREE (&(stte.line));
  FREE (&(stte.param));
}