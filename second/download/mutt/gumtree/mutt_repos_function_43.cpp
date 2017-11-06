static void print_flowed_line (char *line, STATE *s, int ql,
			       flowed_state_t *fst, int term)
{
  size_t width, w, words = 0;
  char *p;
  char last;

  if (!line || !*line)
  {
    /* flush current paragraph (if any) first */
    flush_par (s, fst);
    print_indent (ql, s, 0);
    state_putc ('\n', s);
    return;
  }

  width = quote_width (s, ql);
  last = line[mutt_strlen (line) - 1];

  dprint (4, (debugfile, "f=f: line [%s], width = %ld, spaces = %d\n",
	      NONULL(line), (long)width, fst->spaces));

  for (p = (char *)line, words = 0; (p = strsep (&line, " ")) != NULL ; )
  {
    dprint(4,(debugfile,"f=f: word [%s], width: %d, remaining = [%s]\n",
	      p, fst->width, line));

    /* remember number of spaces */
    if (!*p)
    {
      dprint(4,(debugfile,"f=f: additional space\n"));
      fst->spaces++;
      continue;
    }
    /* there's exactly one space prior to every but the first word */
    if (words)
      fst->spaces++;

    w = mutt_strwidth (p);
    /* see if we need to break the line but make sure the first
       word is put on the line regardless;
       if for DelSp=yes only one trailing space is used, we probably
       have a long word that we should break within (we leave that
       up to the pager or user) */
    if (!(!fst->spaces && fst->delsp && last != ' ') &&
	w < width && w + fst->width + fst->spaces > width)
    {
      dprint(4,(debugfile,"f=f: break line at %d, %d spaces left\n",
		fst->width, fst->spaces));
      /* only honor trailing spaces for format=flowed replies */
      if (option(OPTTEXTFLOWED))
	for ( ; fst->spaces; fst->spaces--)
	  state_putc (' ', s);
      state_putc ('\n', s);
      fst->width = 0;
      fst->spaces = 0;
      words = 0;
    }

    if (!words && !fst->width)
      fst->width = print_indent (ql, s, add_quote_suffix (s, ql));
    fst->width += w + fst->spaces;
    for ( ; fst->spaces; fst->spaces--)
      state_putc (' ', s);
    state_puts (p, s);
    words++;
  }

  if (term)
    flush_par (s, fst);
}