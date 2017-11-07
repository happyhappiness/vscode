static int
display_line (FILE *f, LOFF_T *last_pos, struct line_t **lineInfo, int n, 
	      int *last, int *max, int flags, struct q_class_t **QuoteList,
	      int *q_level, int *force_redraw, regex_t *SearchRE,
              mutt_window_t *pager_window)
{
  unsigned char *buf = NULL, *fmt = NULL;
  size_t buflen = 0;
  unsigned char *buf_ptr = buf;
  int ch, vch, col, cnt, b_read;
  int buf_ready = 0, change_last = 0;
  int special;
  int offset;
  int def_color;
  int m;
  int rc = -1;
  ansi_attr a = {0,0,0,-1};
  regmatch_t pmatch[1];

  if (n == *last)
  {
    (*last)++;
    change_last = 1;
  }

  if (*last == *max)
  {
    safe_realloc (lineInfo, sizeof (struct line_t) * (*max += LINES));
    for (ch = *last; ch < *max ; ch++)
    {
      memset (&((*lineInfo)[ch]), 0, sizeof (struct line_t));
      (*lineInfo)[ch].type = -1;
      (*lineInfo)[ch].search_cnt = -1;
      (*lineInfo)[ch].syntax = safe_malloc (sizeof (struct syntax_t));
      ((*lineInfo)[ch].syntax)[0].first = ((*lineInfo)[ch].syntax)[0].last = -1;
    }
  }

  /* only do color hiliting if we are viewing a message */
  if (flags & (MUTT_SHOWCOLOR | MUTT_TYPES))
  {
    if ((*lineInfo)[n].type == -1)
    {
      /* determine the line class */
      if (fill_buffer (f, last_pos, (*lineInfo)[n].offset, &buf, &fmt, &buflen, &buf_ready) < 0)
      {
	if (change_last)
	  (*last)--;
	goto out;
      }

      resolve_types ((char *) fmt, (char *) buf, *lineInfo, n, *last,
		      QuoteList, q_level, force_redraw, flags & MUTT_SHOWCOLOR);

      /* avoid race condition for continuation lines when scrolling up */
      for (m = n + 1; m < *last && (*lineInfo)[m].offset && (*lineInfo)[m].continuation; m++)
	(*lineInfo)[m].type = (*lineInfo)[n].type;
    }

    /* this also prevents searching through the hidden lines */
    if ((flags & MUTT_HIDE) && (*lineInfo)[n].type == MT_COLOR_QUOTED)
      flags = 0; /* MUTT_NOSHOW */
  }

  /* At this point, (*lineInfo[n]).quote may still be undefined. We 
   * don't want to compute it every time MUTT_TYPES is set, since this
   * would slow down the "bottom" function unacceptably. A compromise
   * solution is hence to call regexec() again, just to find out the
   * length of the quote prefix.
   */
  if ((flags & MUTT_SHOWCOLOR) && !(*lineInfo)[n].continuation &&
      (*lineInfo)[n].type == MT_COLOR_QUOTED && (*lineInfo)[n].quote == NULL)
  {
    if (fill_buffer (f, last_pos, (*lineInfo)[n].offset, &buf, &fmt, &buflen, &buf_ready) < 0)
    {
      if (change_last)
	(*last)--;
      goto out;
    }
    regexec ((regex_t *) QuoteRegexp.rx, (char *) fmt, 1, pmatch, 0);
    (*lineInfo)[n].quote = classify_quote (QuoteList,
			    (char *) fmt + pmatch[0].rm_so,
			    pmatch[0].rm_eo - pmatch[0].rm_so,
			    force_redraw, q_level);
  }

  if ((flags & MUTT_SEARCH) && !(*lineInfo)[n].continuation && (*lineInfo)[n].search_cnt == -1) 
  {
    if (fill_buffer (f, last_pos, (*lineInfo)[n].offset, &buf, &fmt, &buflen, &buf_ready) < 0)
    {
      if (change_last)
	(*last)--;
      goto out;
    }

    offset = 0;
    (*lineInfo)[n].search_cnt = 0;
    while (regexec (SearchRE, (char *) fmt + offset, 1, pmatch, (offset ? REG_NOTBOL : 0)) == 0)
    {
      if (++((*lineInfo)[n].search_cnt) > 1)
	safe_realloc (&((*lineInfo)[n].search),
		      ((*lineInfo)[n].search_cnt) * sizeof (struct syntax_t));
      else
	(*lineInfo)[n].search = safe_malloc (sizeof (struct syntax_t));
      pmatch[0].rm_so += offset;
      pmatch[0].rm_eo += offset;
      ((*lineInfo)[n].search)[(*lineInfo)[n].search_cnt - 1].first = pmatch[0].rm_so;
      ((*lineInfo)[n].search)[(*lineInfo)[n].search_cnt - 1].last = pmatch[0].rm_eo;

      if (pmatch[0].rm_eo == pmatch[0].rm_so)
	offset++; /* avoid degenerate cases */
      else
	offset = pmatch[0].rm_eo;
      if (!fmt[offset])
	break;
    }
  }

  if (!(flags & MUTT_SHOW) && (*lineInfo)[n+1].offset > 0)
  {
    /* we've already scanned this line, so just exit */
    rc = 0;
    goto out;
  }
  if ((flags & MUTT_SHOWCOLOR) && *force_redraw && (*lineInfo)[n+1].offset > 0)
  {
    /* no need to try to display this line... */
    rc = 1;
    goto out; /* fake display */
  }

  if ((b_read = fill_buffer (f, last_pos, (*lineInfo)[n].offset, &buf, &fmt, 
			     &buflen, &buf_ready)) < 0)
  {
    if (change_last)
      (*last)--;
    goto out;
  }

  /* now chose a good place to break the line */
  cnt = format_line (lineInfo, n, buf, flags, 0, b_read, &ch, &vch, &col, &special,
                     pager_window);
  buf_ptr = buf + cnt;

  /* move the break point only if smart_wrap is set */
  if (option (OPTWRAP))
  {
    if (cnt < b_read)
    {
      if (ch != -1 && buf[0] != ' ' && buf[0] != '\t' &&
	  buf[cnt] != ' ' && buf[cnt] != '\t' && buf[cnt] != '\n' && buf[cnt] != '\r')
      {
	buf_ptr = buf + ch;
	/* skip trailing blanks */
	while (ch && (buf[ch] == ' ' || buf[ch] == '\t' || buf[ch] == '\r'))
	  ch--;
        /* a very long word with leading spaces causes infinite wrapping */
        if ((!ch) && (flags & MUTT_PAGER_NSKIP))
          buf_ptr = buf + cnt;
        else
          cnt = ch + 1;
      }
      else
	buf_ptr = buf + cnt; /* a very long word... */
    }
    if (!(flags & MUTT_PAGER_NSKIP))
      /* skip leading blanks on the next line too */
      while (*buf_ptr == ' ' || *buf_ptr == '\t') 
	buf_ptr++;
  }

  if (*buf_ptr == '\r')
    buf_ptr++;
  if (*buf_ptr == '\n')
    buf_ptr++;

  if ((int) (buf_ptr - buf) < b_read && !(*lineInfo)[n+1].continuation)
    append_line (*lineInfo, n, (int) (buf_ptr - buf));
  (*lineInfo)[n+1].offset = (*lineInfo)[n].offset + (long) (buf_ptr - buf);

  /* if we don't need to display the line we are done */
  if (!(flags & MUTT_SHOW))
  {
    rc = 0;
    goto out;
  }

  /* display the line */
  format_line (lineInfo, n, buf, flags, &a, cnt, &ch, &vch, &col, &special,
               pager_window);

  /* avoid a bug in ncurses... */
#ifndef USE_SLANG_CURSES
  if (col == 0)
  {
    NORMAL_COLOR;
    addch (' ');
  }
#endif

  /* end the last color pattern (needed by S-Lang) */
  if (special || (col != pager_window->cols && (flags & (MUTT_SHOWCOLOR | MUTT_SEARCH))))
    resolve_color (*lineInfo, n, vch, flags, 0, &a);
          
  /*
   * Fill the blank space at the end of the line with the prevailing color.
   * ncurses does an implicit clrtoeol() when you do addch('\n') so we have
   * to make sure to reset the color *after* that
   */
  if (flags & MUTT_SHOWCOLOR)
  {
    m = ((*lineInfo)[n].continuation) ? ((*lineInfo)[n].syntax)[0].first : n;
    if ((*lineInfo)[m].type == MT_COLOR_HEADER)
      def_color = ((*lineInfo)[m].syntax)[0].color;
    else
      def_color = ColorDefs[ (*lineInfo)[m].type ];

    ATTRSET(def_color);
  }

  if (col < pager_window->cols)
    mutt_window_clrtoeol (pager_window);

  /*
   * reset the color back to normal.  This *must* come after the
   * clrtoeol, otherwise the color for this line will not be
   * filled to the right margin.
   */
  if (flags & MUTT_SHOWCOLOR)
    NORMAL_COLOR;

  /* build a return code */
  if (!(flags & MUTT_SHOW))
    flags = 0;

  rc = flags;

out:
  FREE(&buf);
  FREE(&fmt);
  return rc;
}