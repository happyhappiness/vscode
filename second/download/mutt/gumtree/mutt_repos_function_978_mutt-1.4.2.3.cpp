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
    if (buf[0] == '\n')
      lineInfo[n].type = MT_COLOR_NORMAL;
    else if (n > 0 && (buf[0] == ' ' || buf[0] == '\t'))
    {
      lineInfo[n].type = lineInfo[n-1].type; /* wrapped line */
      (lineInfo[n].syntax)[0].color = (lineInfo[n-1].syntax)[0].color;
    }
    else
    {
      lineInfo[n].type = MT_COLOR_HDEFAULT;
      color_line = ColorHdrList;
      while (color_line)
      {
	if (REGEXEC (color_line->rx, buf) == 0)
	{
	  lineInfo[n].type = MT_COLOR_HEADER;
	  lineInfo[n].syntax[0].color = color_line->pair;
	  break;
	}
	color_line = color_line->next;
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
	  safe_realloc ((void **) &(lineInfo[n].syntax), 
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
      lineInfo[n].type == MT_COLOR_QUOTED)
  {
    i = 0;

    offset = 0;
    lineInfo[n].chunks = 0;
    do
    {
      if (!buf[offset])
	break;

      found = 0;
      null_rx = 0;
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
	      if (++(lineInfo[n].chunks) > 1)
		safe_realloc ((void **)&(lineInfo[n].syntax), 
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
  }
}