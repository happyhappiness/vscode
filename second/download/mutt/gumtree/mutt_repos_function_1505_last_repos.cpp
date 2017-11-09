static int format_line (struct line_t **lineInfo, int n, unsigned char *buf,
			int flags, ansi_attr *pa, int cnt,
			int *pspace, int *pvch, int *pcol, int *pspecial,
                        mutt_window_t *pager_window)
{
  int space = -1; /* index of the last space or TAB */
  int col = option (OPTMARKERS) ? (*lineInfo)[n].continuation : 0;
  size_t k;
  int ch, vch, last_special = -1, special = 0, t;
  wchar_t wc;
  mbstate_t mbstate;
  int wrap_cols = mutt_window_wrap_cols (pager_window, (flags & MUTT_PAGER_NOWRAP) ? 0 : Wrap);

  if (check_attachment_marker ((char *)buf) == 0)
    wrap_cols = pager_window->cols;

  /* FIXME: this should come from lineInfo */
  memset(&mbstate, 0, sizeof(mbstate));

  for (ch = 0, vch = 0; ch < cnt; ch += k, vch += k)
  {
    /* Handle ANSI sequences */
    while (cnt-ch >= 2 && buf[ch] == '\033' && buf[ch+1] == '[' &&
	   is_ansi (buf+ch+2))
      ch = grok_ansi (buf, ch+2, pa) + 1;

    while (cnt-ch >= 2 && buf[ch] == '\033' && buf[ch+1] == ']' &&
	   check_attachment_marker ((char *) buf+ch) == 0)
    {
      while (buf[ch++] != '\a')
	if (ch >= cnt)
	  break;
    }

    /* is anything left to do? */
    if (ch >= cnt)
      break;
    
    k = mbrtowc (&wc, (char *)buf+ch, cnt-ch, &mbstate);
    if (k == (size_t)(-2) || k == (size_t)(-1))
    {
      if (k == (size_t)(-1))
        memset(&mbstate, 0, sizeof(mbstate));
      dprint (1, (debugfile, "%s:%d: mbrtowc returned %d; errno = %d.\n",
		  __FILE__, __LINE__, k, errno));
      if (col + 4 > wrap_cols)
	break;
      col += 4;
      if (pa)
	printw ("\\%03o", buf[ch]);
      k = 1;
      continue;
    }
    if (k == 0)
      k = 1;

    if (Charset_is_utf8)
    {
      if (wc == 0x200B || wc == 0xFEFF)
      {
	dprint (3, (debugfile, "skip zero-width character U+%04X\n", (unsigned short)wc));
	continue;
      }
      if (is_display_corrupting_utf8 (wc))
      {
	dprint (3, (debugfile, "filtered U+%04X\n", (unsigned short)wc));
	continue;
      }
    }

    /* Handle backspace */
    special = 0;
    if (IsWPrint (wc))
    {
      wchar_t wc1;
      mbstate_t mbstate1;
      size_t k1, k2;

      mbstate1 = mbstate;
      k1 = mbrtowc (&wc1, (char *)buf+ch+k, cnt-ch-k, &mbstate1);
      while ((k1 != (size_t)(-2)) && (k1 != (size_t)(-1)) &&
             (k1 > 0) && (wc1 == '\b'))
      {
        k2 = mbrtowc (&wc1, (char *)buf+ch+k+k1, cnt-ch-k-k1, &mbstate1);
        if ((k2 == (size_t)(-2)) || (k2 == (size_t)(-1)) ||
            (k2 == 0) || (!IsWPrint (wc1)))
          break;

	if (wc == wc1)
	{
	  special |= (wc == '_' && special & A_UNDERLINE)
	    ? A_UNDERLINE : A_BOLD;
	}
	else if (wc == '_' || wc1 == '_')
	{
	  special |= A_UNDERLINE;
	  wc = (wc1 == '_') ? wc : wc1;
	}
	else
	{
	  /* special = 0; / * overstrike: nothing to do! */
	  wc = wc1;
	}

	ch += k + k1;
	k = k2;
	mbstate = mbstate1;
        k1 = mbrtowc (&wc1, (char *)buf+ch+k, cnt-ch-k, &mbstate1);
      }
    }

    if (pa &&
	((flags & (MUTT_SHOWCOLOR | MUTT_SEARCH | MUTT_PAGER_MARKER)) ||
	 special || last_special || pa->attr))
    {
      resolve_color (*lineInfo, n, vch, flags, special, pa);
      last_special = special;
    }

    if (IsWPrint (wc) || (Charset_is_utf8 && wc == 0x00A0))
    {
      if (wc == ' ')
	space = ch;
      else if (Charset_is_utf8 && wc == 0x00A0)
      {
	/* Convert non-breaking space to normal space. The local variable
	 * `space' is not set here so that the caller of this function won't
	 * attempt to wrap at this character. */
	wc = ' ';
      }
      t = wcwidth (wc);
      if (col + t > wrap_cols)
	break;
      col += t;
      if (pa)
	mutt_addwch (wc);
    }
    else if (wc == '\n')
      break;
    else if (wc == '\t')
    {
      space = ch;
      t = (col & ~7) + 8;
      if (t > wrap_cols)
	break;
      if (pa)
	for (; col < t; col++)
	  addch (' ');
      else
	col = t;
    }
    else if (wc < 0x20 || wc == 0x7f)
    {
      if (col + 2 > wrap_cols)
	break;
      col += 2;
      if (pa)
	printw ("^%c", ('@' + wc) & 0x7f);
    }
    else if (wc < 0x100)
    {
      if (col + 4 > wrap_cols)
	break;
      col += 4;
      if (pa)
	printw ("\\%03o", wc);
    }
    else
    {
      if (col + 1 > wrap_cols)
	break;
      ++col;
      if (pa)
	addch (replacement_char ());
    }
  }
  *pspace = space;
  *pcol = col;
  *pvch = vch;
  *pspecial = special;
  return ch;
}