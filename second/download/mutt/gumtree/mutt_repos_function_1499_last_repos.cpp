static void
resolve_types (char *buf, char *raw, struct line_t *lineInfo, int n, int last,
		struct q_class_t **QuoteList, int *q_level, int *force_redraw,
		int q_classify)
{
  COLOR_LINE *color_line;
  regmatch_t pmatch[1], smatch[1];
  int found, offset, null_rx, i;

  if (n == 0 || ISHEADER (lineInfo[n-1].type))
  {
    if (buf[0] == '\n') /* end of header */
    {
      lineInfo[n].type = MT_COLOR_NORMAL;
      getyx(stdscr, brailleLine, brailleCol);
    }
    else
    {
      /* if this is a continuation of the previous line, use the previous
       * line's color as default. */
      if (n > 0 && (buf[0] == ' ' || buf[0] == '\t'))
      {
	lineInfo[n].type = lineInfo[n-1].type; /* wrapped line */
        if (!option (OPTHEADERCOLORPARTIAL))
        {
          (lineInfo[n].syntax)[0].color = (lineInfo[n-1].syntax)[0].color;
          lineInfo[n].is_cont_hdr = 1;
        }
      }
      else
      {
	lineInfo[n].type = MT_COLOR_HDEFAULT;
      }

      /* When this option is unset, we color the entire header the
       * same color.  Otherwise, we handle the header patterns just
       * like body patterns (further below).
       */
      if (!option (OPTHEADERCOLORPARTIAL))
      {
        for (color_line = ColorHdrList; color_line; color_line = color_line->next)
        {
          if (REGEXEC (color_line->rx, buf) == 0)
          {
            lineInfo[n].type = MT_COLOR_HEADER;
            lineInfo[n].syntax[0].color = color_line->pair;
            if (lineInfo[n].is_cont_hdr)
            {
              /* adjust the previous continuation lines to reflect the color of this continuation line */
              int j;
              for (j = n - 1; j >= 0 && lineInfo[j].is_cont_hdr; --j)
              {
                lineInfo[j].type = lineInfo[n].type;
                lineInfo[j].syntax[0].color = lineInfo[n].syntax[0].color;
              }
              /* now adjust the first line of this header field */
              if (j >= 0)
              {
                lineInfo[j].type = lineInfo[n].type;
                lineInfo[j].syntax[0].color = lineInfo[n].syntax[0].color;
              }
              *force_redraw = 1; /* the previous lines have already been drawn on the screen */
            }
            break;
          }
        }
      }
    }
  }
  else if (mutt_strncmp ("\033[0m", raw, 4) == 0)	/* a little hack... */
    lineInfo[n].type = MT_COLOR_NORMAL;
#if 0
  else if (mutt_strncmp ("[-- ", buf, 4) == 0)
    lineInfo[n].type = MT_COLOR_ATTACHMENT;
#else
  else if (check_attachment_marker ((char *) raw) == 0)
    lineInfo[n].type = MT_COLOR_ATTACHMENT;
#endif
  else if (mutt_strcmp ("-- \n", buf) == 0 || mutt_strcmp ("-- \r\n", buf) == 0)
  {
    i = n + 1;

    lineInfo[n].type = MT_COLOR_SIGNATURE;
    while (i < last && check_sig (buf, lineInfo, i - 1) == 0 &&
	   (lineInfo[i].type == MT_COLOR_NORMAL ||
	    lineInfo[i].type == MT_COLOR_QUOTED ||
	    lineInfo[i].type == MT_COLOR_HEADER))
      {
	/* oops... */
	if (lineInfo[i].chunks)
	{
	  lineInfo[i].chunks = 0;
	  safe_realloc (&(lineInfo[n].syntax), 
			sizeof (struct syntax_t));
	}
	lineInfo[i++].type = MT_COLOR_SIGNATURE;
      }
  }
  else if (check_sig (buf, lineInfo, n - 1) == 0)
    lineInfo[n].type = MT_COLOR_SIGNATURE;
  else if (regexec ((regex_t *) QuoteRegexp.rx, buf, 1, pmatch, 0) == 0)
  {
    if (regexec ((regex_t *) Smileys.rx, buf, 1, smatch, 0) == 0)
    {
      if (smatch[0].rm_so > 0)
      {
	char c;

	/* hack to avoid making an extra copy of buf */
	c = buf[smatch[0].rm_so];
	buf[smatch[0].rm_so] = 0;

	if (regexec ((regex_t *) QuoteRegexp.rx, buf, 1, pmatch, 0) == 0)
	{
	  if (q_classify && lineInfo[n].quote == NULL)
	    lineInfo[n].quote = classify_quote (QuoteList,
				  buf + pmatch[0].rm_so,
				  pmatch[0].rm_eo - pmatch[0].rm_so,
				  force_redraw, q_level);
	  lineInfo[n].type = MT_COLOR_QUOTED;
	}
	else
	  lineInfo[n].type = MT_COLOR_NORMAL;

	buf[smatch[0].rm_so] = c;
      }
      else
	lineInfo[n].type = MT_COLOR_NORMAL;
    }
    else
    {
      if (q_classify && lineInfo[n].quote == NULL)
	lineInfo[n].quote = classify_quote (QuoteList, buf + pmatch[0].rm_so,
			      pmatch[0].rm_eo - pmatch[0].rm_so,
			      force_redraw, q_level);
      lineInfo[n].type = MT_COLOR_QUOTED;
    }
  }
  else
    lineInfo[n].type = MT_COLOR_NORMAL;

  /* body patterns */
  if (lineInfo[n].type == MT_COLOR_NORMAL ||
      lineInfo[n].type == MT_COLOR_QUOTED ||
      (lineInfo[n].type == MT_COLOR_HDEFAULT && option (OPTHEADERCOLORPARTIAL)))
  {
    size_t nl;

    /* don't consider line endings part of the buffer
     * for regex matching */
    if ((nl = mutt_strlen (buf)) > 0 && buf[nl-1] == '\n')
      buf[nl-1] = 0;

    i = 0;
    offset = 0;
    lineInfo[n].chunks = 0;
    do
    {
      if (!buf[offset])
	break;

      found = 0;
      null_rx = 0;
      if (lineInfo[n].type == MT_COLOR_HDEFAULT)
        color_line = ColorHdrList;
      else
        color_line = ColorBodyList;
      while (color_line)
      {
	if (regexec (&color_line->rx, buf + offset, 1, pmatch,
		     (offset ? REG_NOTBOL : 0)) == 0)
	{
	  if (pmatch[0].rm_eo != pmatch[0].rm_so)
	  {
	    if (!found)
	    {
              /* Abort if we fill up chunks.
               * Yes, this really happened. See #3888 */
              if (lineInfo[n].chunks == SHRT_MAX)
              {
                null_rx = 0;
                break;
              }
	      if (++(lineInfo[n].chunks) > 1)
		safe_realloc (&(lineInfo[n].syntax), 
			      (lineInfo[n].chunks) * sizeof (struct syntax_t));
	    }
	    i = lineInfo[n].chunks - 1;
	    pmatch[0].rm_so += offset;
	    pmatch[0].rm_eo += offset;
	    if (!found ||
		pmatch[0].rm_so < (lineInfo[n].syntax)[i].first ||
		(pmatch[0].rm_so == (lineInfo[n].syntax)[i].first &&
		 pmatch[0].rm_eo > (lineInfo[n].syntax)[i].last))
	    {
	      (lineInfo[n].syntax)[i].color = color_line->pair;
	      (lineInfo[n].syntax)[i].first = pmatch[0].rm_so;
	      (lineInfo[n].syntax)[i].last = pmatch[0].rm_eo;
	    }
	    found = 1;
	    null_rx = 0;
	  }
	  else
	    null_rx = 1; /* empty regexp; don't add it, but keep looking */
	}
	color_line = color_line->next;
      }

      if (null_rx)
	offset++; /* avoid degenerate cases */
      else
	offset = (lineInfo[n].syntax)[i].last;
    } while (found || null_rx);
    if (nl > 0)
      buf[nl] = '\n';
  }
}