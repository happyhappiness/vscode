int 
mutt_pager (const char *banner, const char *fname, int flags, pager_t *extra)
{
  static char searchbuf[STRING] = "";
  char buffer[LONG_STRING];
  char helpstr[SHORT_STRING*2];
  char tmphelp[SHORT_STRING*2];
  int maxLine, lastLine = 0;
  struct line_t *lineInfo;
  struct q_class_t *QuoteList = NULL;
  int i, j, ch = 0, rc = -1, hideQuoted = 0, q_level = 0, force_redraw = 0;
  int lines = 0, curline = 0, topline = 0, oldtopline = 0, err, first = 1;
  int r = -1, wrapped = 0, searchctx = 0;
  int redraw = REDRAW_FULL;
  FILE *fp = NULL;
  LOFF_T last_pos = 0, last_offset = 0;
  int old_smart_wrap, old_markers;
  struct stat sb;
  regex_t SearchRE;
  int SearchCompiled = 0, SearchFlag = 0, SearchBack = 0;
  int has_types = (IsHeader(extra) || (flags & MUTT_SHOWCOLOR)) ? MUTT_TYPES : 0; /* main message or rfc822 attachment */

  mutt_window_t *index_status_window = NULL;
  mutt_window_t *index_window = NULL;
  mutt_window_t *pager_status_window = NULL;
  mutt_window_t *pager_window = NULL;

  MUTTMENU *index = NULL;		/* the Pager Index (PI) */
  int indexlen = PagerIndexLines;	/* indexlen not always == PIL */
  int indicator = indexlen / 3; 	/* the indicator line of the PI */
  int old_PagerIndexLines;		/* some people want to resize it
  					 * while inside the pager... */

  if (!(flags & MUTT_SHOWCOLOR))
    flags |= MUTT_SHOWFLAT;

  if ((fp = fopen (fname, "r")) == NULL)
  {
    mutt_perror (fname);
    return (-1);
  }

  if (stat (fname, &sb) != 0)
  {
    mutt_perror (fname);
    safe_fclose (&fp);
    return (-1);
  }
  unlink (fname);

  /* Initialize variables */

  if (IsHeader (extra) && !extra->hdr->read)
  {
    Context->msgnotreadyet = extra->hdr->msgno;
    mutt_set_flag (Context, extra->hdr, MUTT_READ, 1);
  }

  lineInfo = safe_malloc (sizeof (struct line_t) * (maxLine = LINES));
  for (i = 0 ; i < maxLine ; i++)
  {
    memset (&lineInfo[i], 0, sizeof (struct line_t));
    lineInfo[i].type = -1;
    lineInfo[i].search_cnt = -1;
    lineInfo[i].syntax = safe_malloc (sizeof (struct syntax_t));
    (lineInfo[i].syntax)[0].first = (lineInfo[i].syntax)[0].last = -1;
  }

  mutt_compile_help (helpstr, sizeof (helpstr), MENU_PAGER, PagerHelp);
  if (IsHeader (extra))
  {
    strfcpy (tmphelp, helpstr, sizeof (tmphelp));
    mutt_compile_help (buffer, sizeof (buffer), MENU_PAGER, PagerHelpExtra);
    snprintf (helpstr, sizeof (helpstr), "%s %s", tmphelp, buffer);
  }
  if (!InHelp)
  {
    strfcpy (tmphelp, helpstr, sizeof (tmphelp));
    mutt_make_help (buffer, sizeof (buffer), _("Help"), MENU_PAGER, OP_HELP);
    snprintf (helpstr, sizeof (helpstr), "%s %s", tmphelp, buffer);
  }

  index_status_window = safe_calloc (sizeof (mutt_window_t), 1);
  index_window        = safe_calloc (sizeof (mutt_window_t), 1);
  pager_status_window = safe_calloc (sizeof (mutt_window_t), 1);
  pager_window        = safe_calloc (sizeof (mutt_window_t), 1);

  while (ch != -1)
  {
    mutt_curs_set (0);

    if (redraw & REDRAW_FULL)
    {
#if ! (defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM))
      mutt_reflow_windows ();
#endif
      NORMAL_COLOR;
      /* clear() doesn't optimize screen redraws */
      move (0, 0);
      clrtobot ();

      if (IsHeader (extra) && Context->vcount + 1 < PagerIndexLines)
	indexlen = Context->vcount + 1;
      else
	indexlen = PagerIndexLines;

      indicator = indexlen / 3;

      memcpy (pager_window, MuttIndexWindow, sizeof(mutt_window_t));
      memcpy (pager_status_window, MuttStatusWindow, sizeof(mutt_window_t));
      index_status_window->rows = index_window->rows = 0;

      if (IsHeader (extra) && PagerIndexLines)
      {
        memcpy (index_window, MuttIndexWindow, sizeof(mutt_window_t));
        index_window->rows = indexlen > 0 ? indexlen - 1 : 0;

        if (option (OPTSTATUSONTOP))
        {
          memcpy (index_status_window, MuttStatusWindow, sizeof(mutt_window_t));

          memcpy (pager_status_window, MuttIndexWindow, sizeof(mutt_window_t));
          pager_status_window->rows = 1;
          pager_status_window->row_offset += index_window->rows;

          pager_window->rows -= index_window->rows + pager_status_window->rows;
          pager_window->row_offset += index_window->rows + pager_status_window->rows;
        }
        else
        {
          memcpy (index_status_window, MuttIndexWindow, sizeof(mutt_window_t));
          index_status_window->rows = 1;
          index_status_window->row_offset += index_window->rows;

          pager_window->rows -= index_window->rows + index_status_window->rows;
          pager_window->row_offset += index_window->rows + index_status_window->rows;
        }
      }

      if (option (OPTHELP))
      {
	SETCOLOR (MT_COLOR_STATUS);
	mutt_window_move (MuttHelpWindow, 0, 0);
	mutt_paddstr (MuttHelpWindow->cols, helpstr);
	NORMAL_COLOR;
      }

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      if (Resize != NULL)
      {
	if ((SearchCompiled = Resize->SearchCompiled))
	{
	  REGCOMP
	    (&SearchRE, searchbuf, REG_NEWLINE | mutt_which_case (searchbuf));
	  SearchFlag = MUTT_SEARCH;
	  SearchBack = Resize->SearchBack;
	}
	lines = Resize->line;
	redraw |= REDRAW_SIGWINCH;

	FREE (&Resize);
      }
#endif

      if (IsHeader (extra) && PagerIndexLines)
      {
	if (index == NULL)
	{
	  /* only allocate the space if/when we need the index.
	     Initialise the menu as per the main index */
	  index = mutt_new_menu(MENU_MAIN);
	  index->make_entry = index_make_entry;
	  index->color = index_color;
	  index->max = Context->vcount;
	  index->current = extra->hdr->virtual;
          index->indexwin = index_window;
          index->statuswin = index_status_window;
	}

	NORMAL_COLOR;
	index->pagelen = index_window->rows;;

	/* some fudge to work out where abouts the indicator should go */
	if (index->current - indicator < 0)
	  index->top = 0;
	else if (index->max - index->current < index->pagelen - indicator)
	  index->top = index->max - index->pagelen;
	else
	  index->top = index->current - indicator;

	menu_redraw_index(index);
      }

      redraw |= REDRAW_BODY | REDRAW_INDEX | REDRAW_STATUS;
#ifdef USE_SIDEBAR
      redraw |= REDRAW_SIDEBAR;
#endif
      mutt_show_error ();
    }

    if (redraw & REDRAW_SIGWINCH)
    {
      i = -1;
      j = -1;
      while (display_line (fp, &last_pos, &lineInfo, ++i, &lastLine, &maxLine,
	     has_types | SearchFlag | (flags & MUTT_PAGER_NOWRAP), &QuoteList, &q_level, &force_redraw,
             &SearchRE, pager_window) == 0)
	if (!lineInfo[i].continuation && ++j == lines)
	{
	  topline = i;
	  if (!SearchFlag)
	    break;
	}
    }

#ifdef USE_SIDEBAR
    if ((redraw & REDRAW_SIDEBAR) || SidebarNeedsRedraw)
    {
      SidebarNeedsRedraw = 0;
      mutt_sb_draw ();
    }
#endif

    if ((redraw & REDRAW_BODY) || topline != oldtopline)
    {
      do {
        mutt_window_move (pager_window, 0, 0);
	curline = oldtopline = topline;
	lines = 0;
	force_redraw = 0;

	while (lines < pager_window->rows && lineInfo[curline].offset <= sb.st_size - 1)
	{
	  if (display_line (fp, &last_pos, &lineInfo, curline, &lastLine, 
			    &maxLine,
			    (flags & MUTT_DISPLAYFLAGS) | hideQuoted | SearchFlag | (flags & MUTT_PAGER_NOWRAP),
			    &QuoteList, &q_level, &force_redraw, &SearchRE,
                            pager_window) > 0)
	    lines++;
	  curline++;
          mutt_window_move (pager_window, lines, 0);
	}
	last_offset = lineInfo[curline].offset;
      } while (force_redraw);

      SETCOLOR (MT_COLOR_TILDE);
      while (lines < pager_window->rows)
      {
	mutt_window_clrtoeol (pager_window);
	if (option (OPTTILDE))
	  addch ('~');
	lines++;
        mutt_window_move (pager_window, lines, 0);
      }
      NORMAL_COLOR;

      /* We are going to update the pager status bar, so it isn't
       * necessary to reset to normal color now. */

      redraw |= REDRAW_STATUS; /* need to update the % seen */
    }

    if (redraw & REDRAW_STATUS)
    {
      struct hdr_format_info hfi;
      char pager_progress_str[4];

      hfi.ctx = Context;
      hfi.pager_progress = pager_progress_str;

      if (last_pos < sb.st_size - 1)
	snprintf(pager_progress_str, sizeof(pager_progress_str), OFF_T_FMT "%%", (100 * last_offset / sb.st_size));
      else
	strfcpy(pager_progress_str, (topline == 0) ? "all" : "end", sizeof(pager_progress_str));

      /* print out the pager status bar */
      mutt_window_move (pager_status_window, 0, 0);
      SETCOLOR (MT_COLOR_STATUS);

      if (IsHeader (extra) || IsMsgAttach (extra))
      {
	size_t l1 = pager_status_window->cols * MB_LEN_MAX;
	size_t l2 = sizeof (buffer);
	hfi.hdr = (IsHeader (extra)) ? extra->hdr : extra->bdy->hdr;
	mutt_make_string_info (buffer, l1 < l2 ? l1 : l2, pager_status_window->cols, NONULL (PagerFmt), &hfi, MUTT_FORMAT_MAKEPRINT);
	mutt_paddstr (pager_status_window->cols, buffer);
      }
      else
      {
	char bn[STRING];
	snprintf (bn, sizeof (bn), "%s (%s)", banner, pager_progress_str);
	mutt_paddstr (pager_status_window->cols, bn);
      }
      NORMAL_COLOR;
      if (option(OPTTSENABLED) && TSSupported)
      {
	menu_status_line (buffer, sizeof (buffer), index, NONULL (TSStatusFormat));
	mutt_ts_status(buffer);
	menu_status_line (buffer, sizeof (buffer), index, NONULL (TSIconFormat));
	mutt_ts_icon(buffer);
      }
    }

    if ((redraw & REDRAW_INDEX) && index)
    {
      /* redraw the pager_index indicator, because the
       * flags for this message might have changed. */
      if (index_window->rows > 0)
        menu_redraw_current (index);

      /* print out the index status bar */
      menu_status_line (buffer, sizeof (buffer), index, NONULL(Status));
 
      mutt_window_move (index_status_window, 0, 0);
      SETCOLOR (MT_COLOR_STATUS);
      mutt_paddstr (index_status_window->cols, buffer);
      NORMAL_COLOR;
    }

    redraw = 0;

    if (option(OPTBRAILLEFRIENDLY)) {
      if (brailleLine!=-1) {
        move(brailleLine+1, 0);
        brailleLine = -1;
      }
    } else
      mutt_window_move (pager_status_window, 0, pager_status_window->cols-1);
    mutt_refresh ();

    if (IsHeader (extra) && OldHdr == extra->hdr && TopLine != topline
        && lineInfo[curline].offset < sb.st_size-1)
    {
      if (TopLine - topline > lines)
        topline += lines;
      else
        topline = TopLine;
      continue;
    }
    else
      OldHdr = NULL;
      
    ch = km_dokey (MENU_PAGER);
    if (ch != -1)
      mutt_clear_error ();
    mutt_curs_set (1);

    if (SigInt)
    {
      mutt_query_exit ();
      continue;
    }
#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    else if (SigWinch)
    {
      mutt_resize_screen ();

      /* Store current position. */
      lines = -1;
      for (i = 0; i <= topline; i++)
	if (!lineInfo[i].continuation)
	  lines++;

      if (flags & MUTT_PAGER_RETWINCH)
      {
	Resize = safe_malloc (sizeof (struct resize));

	Resize->line = lines;
	Resize->SearchCompiled = SearchCompiled;
	Resize->SearchBack = SearchBack;

	ch = -1;
	rc = OP_REFORMAT_WINCH;
      }
      else
      {
	for (i = 0; i < maxLine; i++)
	{
	  lineInfo[i].offset = 0;
	  lineInfo[i].type = -1;
	  lineInfo[i].continuation = 0;
	  lineInfo[i].chunks = 0;
	  lineInfo[i].search_cnt = -1;
	  lineInfo[i].quote = NULL;

	  safe_realloc (&(lineInfo[i].syntax),
			sizeof (struct syntax_t));
	  if (SearchCompiled && lineInfo[i].search)
	      FREE (&(lineInfo[i].search));
	}

	lastLine = 0;
	topline = 0;

	redraw = REDRAW_FULL | REDRAW_SIGWINCH;
	ch = 0;
      }

      SigWinch = 0;
      clearok(stdscr,TRUE);/*force complete redraw*/
      continue;
    }
#endif
    else if (ch == -1)
    {
      ch = 0;
      continue;
    }

    rc = ch;

    switch (ch)
    {
      case OP_EXIT:
	rc = -1;
	ch = -1;
	break;

      case OP_QUIT:
	if (query_quadoption (OPT_QUIT, _("Quit Mutt?")) == MUTT_YES)
	{
	  /* avoid prompting again in the index menu */
	  set_quadoption (OPT_QUIT, MUTT_YES);
	  ch = -1;
	}
	break;

      case OP_NEXT_PAGE:
	if (lineInfo[curline].offset < sb.st_size-1)
	{
	  topline = upNLines (PagerContext, lineInfo, curline, hideQuoted);
	}
	else if (option (OPTPAGERSTOP))
	{
	  /* emulate "less -q" and don't go on to the next message. */
	  mutt_error _("Bottom of message is shown.");
	}
	else
	{
	  /* end of the current message, so display the next message. */
	  rc = OP_MAIN_NEXT_UNDELETED;
	  ch = -1;
	}
	break;

      case OP_PREV_PAGE:
	if (topline != 0)
	{
	  topline = upNLines (pager_window->rows-PagerContext, lineInfo, topline, hideQuoted);
	}
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_NEXT_LINE:
	if (lineInfo[curline].offset < sb.st_size-1)
	{
	  topline++;
	  if (hideQuoted)
	  {
	    while (lineInfo[topline].type == MT_COLOR_QUOTED &&
		   topline < lastLine)
	      topline++;
	  }
	}
	else
	  mutt_error _("Bottom of message is shown.");
	break;

      case OP_PREV_LINE:
	if (topline)
	  topline = upNLines (1, lineInfo, topline, hideQuoted);
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_PAGER_TOP:
        if (topline)
	  topline = 0;
      	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_HALF_UP:
	if (topline)
	  topline = upNLines (pager_window->rows/2, lineInfo, topline, hideQuoted);
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_HALF_DOWN:
	if (lineInfo[curline].offset < sb.st_size-1)
	{
	  topline = upNLines (pager_window->rows/2, lineInfo, curline, hideQuoted);
	}
	else if (option (OPTPAGERSTOP))
	{
	  /* emulate "less -q" and don't go on to the next message. */
	  mutt_error _("Bottom of message is shown.");
	}
	else
	{
	  /* end of the current message, so display the next message. */
	  rc = OP_MAIN_NEXT_UNDELETED;
	  ch = -1;
	}
	break;

      case OP_SEARCH_NEXT:
      case OP_SEARCH_OPPOSITE:
	if (SearchCompiled)
	{
	  wrapped = 0;

	  if (SearchContext > 0 && SearchContext < pager_window->rows)
	    searchctx = SearchContext;
	  else
	    searchctx = 0;

search_next:
	  if ((!SearchBack && ch==OP_SEARCH_NEXT) ||
	      (SearchBack &&ch==OP_SEARCH_OPPOSITE))
	  {
	    /* searching forward */
	    for (i = wrapped ? 0 : topline + searchctx + 1; i < lastLine; i++)
	    {
	      if ((!hideQuoted || lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i < lastLine)
	      topline = i;
	    else if (wrapped || !option (OPTWRAPSEARCH))
	      mutt_error _("Not found.");
	    else
	    {
	      mutt_message _("Search wrapped to top.");
	      wrapped = 1;
	      goto search_next;
	    }
	  }
	  else
	  {
	    /* searching backward */
	    for (i = wrapped ? lastLine : topline + searchctx - 1; i >= 0; i--)
	    {
	      if ((!hideQuoted || (has_types && 
		    lineInfo[i].type != MT_COLOR_QUOTED)) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i >= 0)
	      topline = i;
	    else if (wrapped || !option (OPTWRAPSEARCH))
	      mutt_error _("Not found.");
	    else
	    {
	      mutt_message _("Search wrapped to bottom.");
	      wrapped = 1;
	      goto search_next;
	    }
	  }

	  if (lineInfo[topline].search_cnt > 0)
	  {
	    SearchFlag = MUTT_SEARCH;
	    /* give some context for search results */
	    if (topline - searchctx > 0)
	      topline -= searchctx;
	  }

	  break;
	}
	/* no previous search pattern, so fall through to search */

      case OP_SEARCH:
      case OP_SEARCH_REVERSE:
        strfcpy (buffer, searchbuf, sizeof (buffer));
	if (mutt_get_field ((ch == OP_SEARCH || ch == OP_SEARCH_NEXT) ?
			    _("Search for: ") : _("Reverse search for: "),
			    buffer, sizeof (buffer),
			    MUTT_CLEAR) != 0)
	  break;

	if (!strcmp (buffer, searchbuf))
	{
	  if (SearchCompiled)
	  {
	    /* do an implicit search-next */
	    if (ch == OP_SEARCH)
	      ch = OP_SEARCH_NEXT;
	    else
	      ch = OP_SEARCH_OPPOSITE;

	    wrapped = 0;
	    goto search_next;
	  }
	}
      
        if (!buffer[0])
	  break;
      
	strfcpy (searchbuf, buffer, sizeof (searchbuf));

	/* leave SearchBack alone if ch == OP_SEARCH_NEXT */
	if (ch == OP_SEARCH)
	  SearchBack = 0;
	else if (ch == OP_SEARCH_REVERSE)
	  SearchBack = 1;

	if (SearchCompiled)
	{
	  regfree (&SearchRE);
	  for (i = 0; i < lastLine; i++)
	  {
	    if (lineInfo[i].search)
	      FREE (&(lineInfo[i].search));
	    lineInfo[i].search_cnt = -1;
	  }
	}

	if ((err = REGCOMP (&SearchRE, searchbuf, REG_NEWLINE | mutt_which_case (searchbuf))) != 0)
	{
	  regerror (err, &SearchRE, buffer, sizeof (buffer));
	  mutt_error ("%s", buffer);
	  for (i = 0; i < maxLine ; i++)
	  {
	    /* cleanup */
	    if (lineInfo[i].search)
	      FREE (&(lineInfo[i].search));
	    lineInfo[i].search_cnt = -1;
	  }
	  SearchFlag = 0;
	  SearchCompiled = 0;
	}
	else
	{
	  SearchCompiled = 1;
	  /* update the search pointers */
	  i = 0;
	  while (display_line (fp, &last_pos, &lineInfo, i, &lastLine, 
				&maxLine, MUTT_SEARCH | (flags & MUTT_PAGER_NSKIP) | (flags & MUTT_PAGER_NOWRAP),
				&QuoteList, &q_level,
                               &force_redraw, &SearchRE, pager_window) == 0)
	    i++;

	  if (!SearchBack)
	  {
	    /* searching forward */
	    for (i = topline; i < lastLine; i++)
	    {
	      if ((!hideQuoted || lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i < lastLine) topline = i;
	  }
	  else
	  {
	    /* searching backward */
	    for (i = topline; i >= 0; i--)
	    {
	      if ((!hideQuoted || lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i >= 0) topline = i;
	  }

	  if (lineInfo[topline].search_cnt == 0)
	  {
	    SearchFlag = 0;
	    mutt_error _("Not found.");
	  }
	  else
	  {
	    SearchFlag = MUTT_SEARCH;
	    /* give some context for search results */
	    if (SearchContext > 0 && SearchContext < pager_window->rows)
	      searchctx = SearchContext;
	    else
	      searchctx = 0;
	    if (topline - searchctx > 0)
	      topline -= searchctx;
	  }

	}
	redraw = REDRAW_BODY;
	break;

      case OP_SEARCH_TOGGLE:
	if (SearchCompiled)
	{
	  SearchFlag ^= MUTT_SEARCH;
	  redraw = REDRAW_BODY;
	}
	break;

      case OP_HELP:
	/* don't let the user enter the help-menu from the help screen! */
	if (! InHelp)
	{
	  InHelp = 1;
	  mutt_help (MENU_PAGER);
	  redraw = REDRAW_FULL;
	  InHelp = 0;
	}
	else
	  mutt_error _("Help is currently being shown.");
	break;

      case OP_PAGER_HIDE_QUOTED:
	if (has_types)
	{
	  hideQuoted ^= MUTT_HIDE;
	  if (hideQuoted && lineInfo[topline].type == MT_COLOR_QUOTED)
	    topline = upNLines (1, lineInfo, topline, hideQuoted);
	  else
	    redraw = REDRAW_BODY;
	}
	break;

      case OP_PAGER_SKIP_QUOTED:
	if (has_types)
	{
	  int dretval = 0;
	  int new_topline = topline;

	  while ((new_topline < lastLine ||
		  (0 == (dretval = display_line (fp, &last_pos, &lineInfo,
			 new_topline, &lastLine, &maxLine, MUTT_TYPES | (flags & MUTT_PAGER_NOWRAP),
                         &QuoteList, &q_level, &force_redraw, &SearchRE, pager_window))))
		 && lineInfo[new_topline].type != MT_COLOR_QUOTED)
	    new_topline++;

	  if (dretval < 0)
	  {
	    mutt_error _("No more quoted text.");
	    break;
	  }

	  while ((new_topline < lastLine ||
		  (0 == (dretval = display_line (fp, &last_pos, &lineInfo,
			 new_topline, &lastLine, &maxLine, MUTT_TYPES | (flags & MUTT_PAGER_NOWRAP),
                         &QuoteList, &q_level, &force_redraw, &SearchRE, pager_window))))
		 && lineInfo[new_topline].type == MT_COLOR_QUOTED)
	    new_topline++;

	  if (dretval < 0)
	  {
	    mutt_error _("No more unquoted text after quoted text.");
	    break;	  
	  }
	  topline = new_topline;
	}
	break;

      case OP_PAGER_BOTTOM: /* move to the end of the file */
	if (lineInfo[curline].offset < sb.st_size - 1)
	{
	  i = curline;
	  /* make sure the types are defined to the end of file */
	  while (display_line (fp, &last_pos, &lineInfo, i, &lastLine, 
				&maxLine, has_types | (flags & MUTT_PAGER_NOWRAP),
				&QuoteList, &q_level, &force_redraw,
                               &SearchRE, pager_window) == 0)
	    i++;
	  topline = upNLines (pager_window->rows, lineInfo, lastLine, hideQuoted);
	}
	else
	  mutt_error _("Bottom of message is shown.");
	break;

      case OP_REDRAW:
	clearok (stdscr, TRUE);
	redraw = REDRAW_FULL;
	break;

      case OP_NULL:
	km_error_key (MENU_PAGER);
	break;

	/* --------------------------------------------------------------------
	 * The following are operations on the current message rather than
	 * adjusting the view of the message.
	 */

      case OP_BOUNCE_MESSAGE:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra))
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_bounce (extra->fp, extra->hdr,
			      extra->idx, extra->idxlen,
			      extra->bdy);
        else
          ci_bounce_message (extra->hdr, &redraw);
	break;

      case OP_RESEND:
        CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra))
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_resend (extra->fp, extra->hdr,
			      extra->idx, extra->idxlen,
			      extra->bdy);
        else
	  mutt_resend_message (NULL, extra->ctx, extra->hdr);
        redraw = REDRAW_FULL;
        break;

      case OP_CHECK_TRADITIONAL:
        CHECK_MODE (IsHeader (extra));
        if (!(WithCrypto & APPLICATION_PGP))
	  break;
        if (!(extra->hdr->security & PGP_TRADITIONAL_CHECKED)) 
        {
	  ch = -1;
	  rc = OP_CHECK_TRADITIONAL;
	}
        break;
      
      case OP_CREATE_ALIAS:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        if (IsMsgAttach (extra))
	  mutt_create_alias (extra->bdy->hdr->env, NULL);
        else
	  mutt_create_alias (extra->hdr->env, NULL);
	MAYBE_REDRAW (redraw);
	break;

      case OP_PURGE_MESSAGE:
      case OP_DELETE:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot delete message"));

	mutt_set_flag (Context, extra->hdr, MUTT_DELETE, 1);
	mutt_set_flag (Context, extra->hdr, MUTT_PURGE, (ch == OP_PURGE_MESSAGE));
        if (option (OPTDELETEUNTAG))
	  mutt_set_flag (Context, extra->hdr, MUTT_TAG, 0);
	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_MAIN_SET_FLAG:
      case OP_MAIN_CLEAR_FLAG:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;

	if (mutt_change_flag (extra->hdr, (ch == OP_MAIN_SET_FLAG)) == 0)
	  redraw |= REDRAW_STATUS | REDRAW_INDEX;
	if (extra->hdr->deleted && option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_DELETE_THREAD:
      case OP_DELETE_SUBTHREAD:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot delete message(s)"));

	r = mutt_thread_set_flag (extra->hdr, MUTT_DELETE, 1,
				  ch == OP_DELETE_THREAD ? 0 : 1);

	if (r != -1)
	{
	  if (option (OPTDELETEUNTAG))
	    mutt_thread_set_flag (extra->hdr, MUTT_TAG, 0,
				  ch == OP_DELETE_THREAD ? 0 : 1);
	  if (option (OPTRESOLVE))
	  {
	    rc = OP_MAIN_NEXT_UNDELETED;
	    ch = -1;
	  }

	  if (!option (OPTRESOLVE) && PagerIndexLines)
	    redraw = REDRAW_FULL;
	  else
	    redraw = REDRAW_STATUS | REDRAW_INDEX;
	}
	break;

      case OP_DISPLAY_ADDRESS:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        if (IsMsgAttach (extra))
	  mutt_display_address (extra->bdy->hdr->env);
        else
	  mutt_display_address (extra->hdr->env);
	break;

      case OP_ENTER_COMMAND:
	old_smart_wrap = option (OPTWRAP);
	old_markers = option (OPTMARKERS);
	old_PagerIndexLines = PagerIndexLines;

	CurrentMenu = MENU_PAGER;
	mutt_enter_command ();

	if (option (OPTNEEDRESORT))
	{
	  unset_option (OPTNEEDRESORT);
	  CHECK_MODE(IsHeader (extra));
	  set_option (OPTNEEDRESORT);
	}

	if (old_PagerIndexLines != PagerIndexLines)
	{
	  if (index)
	    mutt_menuDestroy (&index);
	  index = NULL;
	}
	
	if (option (OPTWRAP) != old_smart_wrap || 
	    option (OPTMARKERS) != old_markers)
	{
	  if (flags & MUTT_PAGER_RETWINCH)
	  {
	    ch = -1;
	    rc = OP_REFORMAT_WINCH;
	    continue;
	  }

	  /* count the real lines above */
	  j = 0;
	  for (i = 0; i <= topline; i++)
	  {
	    if (!lineInfo[i].continuation)
	      j++;
	  }

	  /* we need to restart the whole thing */
	  for (i = 0; i < maxLine; i++)
	  {
	    lineInfo[i].offset = 0;
	    lineInfo[i].type = -1;
	    lineInfo[i].continuation = 0;
	    lineInfo[i].chunks = 0;
	    lineInfo[i].search_cnt = -1;
	    lineInfo[i].quote = NULL;

	    safe_realloc (&(lineInfo[i].syntax), sizeof (struct syntax_t));
	    if (SearchCompiled && lineInfo[i].search)
		FREE (&(lineInfo[i].search));
	  }

	  if (SearchCompiled)
	  {
	    regfree (&SearchRE);
	    SearchCompiled = 0;
	  }
	  SearchFlag = 0;

	  /* try to keep the old position */
	  topline = 0;
	  lastLine = 0;
	  while (j > 0 && display_line (fp, &last_pos, &lineInfo, topline, 
					&lastLine, &maxLine,
					(has_types ? MUTT_TYPES : 0) | (flags & MUTT_PAGER_NOWRAP),
					&QuoteList, &q_level, &force_redraw,
					&SearchRE, pager_window) == 0)
	  {
	    if (! lineInfo[topline].continuation)
	      j--;
	    if (j > 0)
	      topline++;
	  }

	  ch = 0;
	}

	if (option (OPTFORCEREDRAWPAGER))
	  redraw = REDRAW_FULL;
	unset_option (OPTFORCEREDRAWINDEX);
	unset_option (OPTFORCEREDRAWPAGER);
	break;

      case OP_FLAG_MESSAGE:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_WRITE, "Cannot flag message");

	mutt_set_flag (Context, extra->hdr, MUTT_FLAG, !extra->hdr->flagged);
	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_PIPE:
	CHECK_MODE(IsHeader (extra) || IsAttach (extra));
	if (IsAttach (extra))
	  mutt_pipe_attachment_list (extra->fp, 0, extra->bdy, 0);
	else
	  mutt_pipe_message (extra->hdr);
	MAYBE_REDRAW (redraw);
	break;

      case OP_PRINT:
	CHECK_MODE(IsHeader (extra) || IsAttach (extra));
        if (IsAttach (extra))
	  mutt_print_attachment_list (extra->fp, 0, extra->bdy);
        else
	  mutt_print_message (extra->hdr);
	break;

      case OP_MAIL:
	CHECK_MODE(IsHeader (extra) && !IsAttach (extra));
        CHECK_ATTACH;      
	ci_send_message (0, NULL, NULL, extra->ctx, NULL);
	redraw = REDRAW_FULL;
	break;

      case OP_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;      
        if (IsMsgAttach (extra)) 
	  mutt_attach_reply (extra->fp, extra->hdr, extra->idx,
			     extra->idxlen, extra->bdy,
			     SENDREPLY);
	else
	  ci_send_message (SENDREPLY, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;

      case OP_RECALL_MESSAGE:
	CHECK_MODE(IsHeader (extra) && !IsAttach(extra));
        CHECK_ATTACH;
	ci_send_message (SENDPOSTPONED, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;

      case OP_GROUP_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_reply (extra->fp, extra->hdr, extra->idx,
			     extra->idxlen, extra->bdy, SENDREPLY|SENDGROUPREPLY);
        else
	  ci_send_message (SENDREPLY | SENDGROUPREPLY, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;

      case OP_LIST_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;        
        if (IsMsgAttach (extra))
	  mutt_attach_reply (extra->fp, extra->hdr, extra->idx,
			     extra->idxlen, extra->bdy, SENDREPLY|SENDLISTREPLY);
        else
	  ci_send_message (SENDREPLY | SENDLISTREPLY, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;

      case OP_FORWARD_MESSAGE:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_forward (extra->fp, extra->hdr, extra->idx,
			       extra->idxlen, extra->bdy);
        else
	  ci_send_message (SENDFORWARD, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;

      case OP_DECRYPT_SAVE:
        if (!WithCrypto)
        {
          ch = -1;
          break;
        }
	/* fall through */
      case OP_SAVE:
	if (IsAttach (extra))
	{
	  mutt_save_attachment_list (extra->fp, 0, extra->bdy, extra->hdr, NULL);
	  break;
	}
	/* fall through */
      case OP_COPY_MESSAGE:
      case OP_DECODE_SAVE:
      case OP_DECODE_COPY:
      case OP_DECRYPT_COPY:
        if (!WithCrypto && ch == OP_DECRYPT_COPY)
        {
          ch = -1;
          break;
        }
	CHECK_MODE(IsHeader (extra));
	if (mutt_save_message (extra->hdr,
			       (ch == OP_DECRYPT_SAVE) ||
			       (ch == OP_SAVE) || (ch == OP_DECODE_SAVE),
			       (ch == OP_DECODE_SAVE) || (ch == OP_DECODE_COPY),
			       (ch == OP_DECRYPT_SAVE) || (ch == OP_DECRYPT_COPY) ||
			       0,
			       &redraw) == 0 && (ch == OP_SAVE || ch == OP_DECODE_SAVE
						 || ch == OP_DECRYPT_SAVE
						 ))
	{
	  if (option (OPTRESOLVE))
	  {
	    ch = -1;
	    rc = OP_MAIN_NEXT_UNDELETED;
	  }
	  else
	    redraw |= REDRAW_STATUS | REDRAW_INDEX;
	}
	MAYBE_REDRAW (redraw);
	break;

      case OP_SHELL_ESCAPE:
	mutt_shell_escape ();
	MAYBE_REDRAW (redraw);
	break;

      case OP_TAG:
	CHECK_MODE(IsHeader (extra));
	mutt_set_flag (Context, extra->hdr, MUTT_TAG, !extra->hdr->tagged);

	Context->last_tag = extra->hdr->tagged ? extra->hdr :
	  ((Context->last_tag == extra->hdr && !extra->hdr->tagged)
	   ? NULL : Context->last_tag);

	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_NEXT_ENTRY;
	}
	break;

      case OP_TOGGLE_NEW:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_SEEN, _("Cannot toggle new"));

	if (extra->hdr->read || extra->hdr->old)
	  mutt_set_flag (Context, extra->hdr, MUTT_NEW, 1);
	else if (!first)
	  mutt_set_flag (Context, extra->hdr, MUTT_READ, 1);
	first = 0;
        Context->msgnotreadyet = -1;
	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_UNDELETE:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot undelete message"));

	mutt_set_flag (Context, extra->hdr, MUTT_DELETE, 0);
	mutt_set_flag (Context, extra->hdr, MUTT_PURGE, 0);
	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_NEXT_ENTRY;
	}
	break;

      case OP_UNDELETE_THREAD:
      case OP_UNDELETE_SUBTHREAD:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot undelete message(s)"));

	r = mutt_thread_set_flag (extra->hdr, MUTT_DELETE, 0,
				  ch == OP_UNDELETE_THREAD ? 0 : 1);
	if (r != -1)
          r = mutt_thread_set_flag (extra->hdr, MUTT_PURGE, 0,
                                    ch == OP_UNDELETE_THREAD ? 0 : 1);
	if (r != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    rc = (ch == OP_DELETE_THREAD) ?
				  OP_MAIN_NEXT_THREAD : OP_MAIN_NEXT_SUBTHREAD;
	    ch = -1;
	  }

	  if (!option (OPTRESOLVE) && PagerIndexLines)
	    redraw = REDRAW_FULL;
	  else
	    redraw = REDRAW_STATUS | REDRAW_INDEX;
	}
	break;

      case OP_VERSION:
	mutt_version ();
	break;

      case OP_BUFFY_LIST:
	mutt_buffy_list ();
	break;

      case OP_VIEW_ATTACHMENTS:
        if (flags & MUTT_PAGER_ATTACHMENT)
        {
	  ch = -1;
	  rc = OP_ATTACH_COLLAPSE;
	  break;
	}
	CHECK_MODE(IsHeader (extra));
	mutt_view_attachments (extra->hdr);
	if (extra->hdr->attach_del)
	  Context->changed = 1;
	redraw = REDRAW_FULL;
	break;


      case OP_MAIL_KEY:
        if (!(WithCrypto & APPLICATION_PGP))
        {
          ch = -1;
          break;
        }
	CHECK_MODE(IsHeader(extra));
        CHECK_ATTACH;
	ci_send_message (SENDKEY, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;


      case OP_FORGET_PASSPHRASE:
	crypt_forget_passphrase ();
	break;

      case OP_EXTRACT_KEYS:
        if (!WithCrypto)
        {
          ch = -1;
          break;
        }
        CHECK_MODE(IsHeader(extra));
	crypt_extract_keys_from_messages(extra->hdr);
        redraw = REDRAW_FULL;
        break;

      case OP_WHAT_KEY:
	mutt_what_key ();
	break;

#ifdef USE_SIDEBAR
      case OP_SIDEBAR_NEXT:
      case OP_SIDEBAR_NEXT_NEW:
      case OP_SIDEBAR_PAGE_DOWN:
      case OP_SIDEBAR_PAGE_UP:
      case OP_SIDEBAR_PREV:
      case OP_SIDEBAR_PREV_NEW:
	mutt_sb_change_mailbox (ch);
	break;

      case OP_SIDEBAR_TOGGLE_VISIBLE:
	toggle_option (OPTSIDEBAR);
        mutt_reflow_windows();
	redraw = REDRAW_FULL;
	break;
#endif

      default:
	ch = -1;
	break;
    }
  }

  safe_fclose (&fp);
  if (IsHeader (extra))
  {
    Context->msgnotreadyet = -1;
    if (rc == -1)
      OldHdr = NULL;
    else
    {
      TopLine = topline;
      OldHdr = extra->hdr;
    }
  }
    
  cleanup_quote (&QuoteList);
  
  for (i = 0; i < maxLine ; i++)
  {
    FREE (&(lineInfo[i].syntax));
    if (SearchCompiled && lineInfo[i].search)
      FREE (&(lineInfo[i].search));
  }
  if (SearchCompiled)
  {
    regfree (&SearchRE);
    SearchCompiled = 0;
  }
  FREE (&lineInfo);
  if (index)
    mutt_menuDestroy(&index);

  FREE (&index_status_window);
  FREE (&index_window);
  FREE (&pager_status_window);
  FREE (&pager_window);

  return (rc != -1 ? rc : 0);
}