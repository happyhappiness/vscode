static int fold_one_header (FILE *fp, const char *tag, const char *value,
			      const char *pfx, int wraplen, int flags)
{
  const char *p = value, *next, *sp;
  char buf[HUGE_STRING] = "";
  int first = 1, enc, col = 0, w, l = 0, fold;

  dprint(4,(debugfile,"mwoh: pfx=[%s], tag=[%s], flags=%d value=[%s]\n",
	    pfx, tag, flags, value));

  if (tag && *tag && fprintf (fp, "%s%s: ", NONULL (pfx), tag) < 0)
    return -1;
  col = mutt_strlen (tag) + (tag && *tag ? 2 : 0) + mutt_strlen (pfx);

  while (p && *p)
  {
    fold = 0;

    /* find the next word and place it in `buf'. it may start with
     * whitespace we can fold before */
    next = find_word (p);
    l = MIN(sizeof (buf) - 1, next - p);
    memcpy (buf, p, l);
    buf[l] = 0;

    /* determine width: character cells for display, bytes for sending
     * (we get pure ascii only) */
    w = my_width (buf, col, flags);
    enc = mutt_strncmp (buf, "=?", 2) == 0;

    dprint(5,(debugfile,"mwoh: word=[%s], col=%d, w=%d, next=[0x0%x]\n",
	      buf, col, w, *next));

    /* insert a folding \n before the current word's lwsp except for
     * header name, first word on a line (word longer than wrap width)
     * and encoded words */
    if (!first && !enc && col && col + w >= wraplen)
    {
      col = mutt_strlen (pfx);
      fold = 1;
      if (fprintf (fp, "\n%s", NONULL(pfx)) <= 0)
	return -1;
    }

    /* print the actual word; for display, ignore leading ws for word
     * and fold with tab for readability */
    if ((flags & CH_DISPLAY) && fold)
    {
      char *p = buf;
      while (*p && (*p == ' ' || *p == '\t'))
      {
	p++;
	col--;
      }
      if (fputc ('\t', fp) == EOF)
	return -1;
      if (print_val (fp, pfx, p, flags, col) < 0)
	return -1;
      col += 8;
    }
    else if (print_val (fp, pfx, buf, flags, col) < 0)
      return -1;
    col += w;

    /* if the current word ends in \n, ignore all its trailing spaces
     * and reset column; this prevents us from putting only spaces (or
     * even none) on a line if the trailing spaces are located at our
     * current line width
     * XXX this covers ASCII space only, for display we probably
     * XXX want something like iswspace() here */
    sp = next;
    while (*sp && (*sp == ' ' || *sp == '\t'))
      sp++;
    if (*sp == '\n')
    {
      next = sp;
      col = 0;
    }

    p = next;
    first = 0;
  }

  /* if we have printed something but didn't \n-terminate it, do it
   * except the last word we printed ended in \n already */
  if (col && buf[l - 1] != '\n')
    if (putc ('\n', fp) == EOF)
      return -1;

  return 0;
}