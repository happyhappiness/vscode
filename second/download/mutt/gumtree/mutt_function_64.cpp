int 
mutt_pager (const char *banner, const char *fname, int flags, pager_t *extra)
{
  static char searchbuf[STRING];
  char buffer[LONG_STRING];
  char helpstr[SHORT_STRING*2];
  char tmphelp[SHORT_STRING*2];
  int maxLine, lastLine = 0;
  struct line_t *lineInfo;
  struct q_class_t *QuoteList = NULL;
  int i, j, ch = 0, rc = -1, hideQuoted = 0, q_level = 0, force_redraw = 0;
  int lines = 0, curline = 0, topline = 0, oldtopline = 0, err, first = 1;
  int r = -1;
  int redraw = REDRAW_FULL;
  FILE *fp = NULL;
  long last_pos = 0, last_offset = 0;
  int old_smart_wrap, old_markers;
  struct stat sb;
  regex_t SearchRE;
  int SearchCompiled = 0, SearchFlag = 0, SearchBack = 0;
  int has_types = (IsHeader(extra) || (flags & M_SHOWCOLOR)) ? M_TYPES : 0; /* main message or rfc822 attachment */

  int bodyoffset = 1;			/* offset of first line of real text */
  int statusoffset = 0; 		/* offset for the status bar */
  int helpoffset = LINES - 2;		/* offset for the help bar. */
  int bodylen = LINES - 2 - bodyoffset; /* length of displayable area */

  MUTTMENU *index = NULL;		/* the Pager Index (PI) */
  int indexoffset = 0;			/* offset for the PI */
  int indexlen = PagerIndexLines;	/* indexlen not always == PIL */
  int indicator = indexlen / 3; 	/* the indicator line of the PI */
  int old_PagerIndexLines;		/* some people want to resize it
  					 * while inside the pager... */

  if (!(flags & M_SHOWCOLOR))
    flags |= M_SHOWFLAT;

  if ((fp = fopen (fname, "r")) == NULL)
  {
    mutt_perror (fname);
    return (-1);
  }

  if (stat (fname, &sb) != 0)
  {
    mutt_perror (fname);
    fclose (fp);
    return (-1);
  }
  unlink (fname);

  /* Initialize variables */

  if (IsHeader (extra) && !extra->hdr->read)
  {
    Context->msgnotreadyet = extra->hdr->msgno;
    mutt_set_flag (Context, extra->hdr, M_READ, 1);
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

  while (ch != -1)
  {
    mutt_curs_set (0);

#ifdef USE_IMAP
    imap_keepalive ();
#endif
    
    if (redraw & REDRAW_FULL)
    {
      SETCOLOR (MT_COLOR_NORMAL);
      /* clear() doesn't optimize screen redraws */
      move (0, 0);
      clrtobot ();

      if (IsHeader (extra) && Context->vcount + 1 < PagerIndexLines)
	indexlen = Context->vcount + 1;
      else
	indexlen = PagerIndexLines;

      indicator = indexlen / 3;

      if (option (OPTSTATUSONTOP))
      {
	indexoffset = 0;
	statusoffset = IsHeader (extra) ? indexlen : 0;
	bodyoffset = statusoffset + 1;
	helpoffset = LINES - 2;
	bodylen = helpoffset - bodyoffset;
	if (!option (OPTHELP))
	  bodylen++;
      }
      else
      {
	helpoffset = 0;
	indexoffset = 1;
	statusoffset = LINES - 2;
	if (!option (OPTHELP))
	  indexoffset = 0;
	bodyoffset = indexoffset + (IsHeader (extra) ? indexlen : 0);
	bodylen = statusoffset - bodyoffset;
      }

      if (option (OPTHELP))
      {
	SETCOLOR (MT_COLOR_STATUS);
	move (helpoffset, 0);
	mutt_paddstr (COLS, helpstr);
	SETCOLOR (MT_COLOR_NORMAL);
      }

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      if (Resize != NULL)
      {
	if ((SearchCompiled = Resize->SearchCompiled))
	{
	  REGCOMP
	    (&SearchRE, searchbuf, REG_NEWLINE | mutt_which_case (searchbuf));
	  SearchFlag = M_SEARCH;
	  SearchBack = Resize->SearchBack;
	}
	lines = Resize->line;
	redraw |= REDRAW_SIGWINCH;

	safe_free ((void **) &Resize);
      }
#endif

      if (IsHeader (extra) && PagerIndexLines)
      {
	if (index == NULL)
	{
	  /* only allocate the space if/when we need the index.
	     Initialise the menu as per the main index */
	  index = mutt_new_menu();
	  index->menu = MENU_MAIN;
	  index->make_entry = index_make_entry;
	  index->color = index_color;
	  index->max = Context->vcount;
	  index->current = extra->hdr->virtual;
	}

	SETCOLOR (MT_COLOR_NORMAL);
	index->offset  = indexoffset + (option (OPTSTATUSONTOP) ? 1 : 0);

	index->pagelen = indexlen - 1;

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
      mutt_show_error ();
    }

    if (redraw & REDRAW_SIGWINCH)
    {
      i = -1;
      j = -1;
      while (display_line (fp, &last_pos, &lineInfo, ++i, &lastLine, &maxLine,
	     has_types | SearchFlag, &QuoteList, &q_level, &force_redraw,
	     &SearchRE) == 0)
	if (!lineInfo[i].continuation && ++j == lines)
	{
	  topline = i;
	  if (!SearchFlag)
	    break;
	}
    }

    if ((redraw & REDRAW_BODY) || topline != oldtopline)
    {
      do {
	move (bodyoffset, 0);
	curline = oldtopline = topline;
	lines = 0;
	force_redraw = 0;

	while (lines < bodylen && lineInfo[curline].offset <= sb.st_size - 1)
	{
	  if (display_line (fp, &last_pos, &lineInfo, curline, &lastLine, 
			    &maxLine,
			    (flags & M_DISPLAYFLAGS) | hideQuoted | SearchFlag, 
			    &QuoteList, &q_level, &force_redraw, &SearchRE) > 0)
	    lines++;
	  curline++;
	}
	last_offset = lineInfo[curline].offset;
      } while (force_redraw);

      SETCOLOR (MT_COLOR_TILDE);
      BKGDSET (MT_COLOR_TILDE);
      while (lines < bodylen)
      {
	clrtoeol ();
	if (option (OPTTILDE))
	  addch ('~');
	addch ('\n');
	lines++;
      }
      /* We are going to update the pager status bar, so it isn't
       * necessary to reset to normal color now. */

      redraw |= REDRAW_STATUS; /* need to update the % seen */
    }

    if (redraw & REDRAW_STATUS)
    {
      /* print out the pager status bar */
      SETCOLOR (MT_COLOR_STATUS);
      BKGDSET (MT_COLOR_STATUS);
      CLEARLINE (statusoffset);
      if (IsHeader (extra))
      {
	_mutt_make_string (buffer,
			   COLS-9 < sizeof (buffer) ? COLS-9 : sizeof (buffer),
			   NONULL (PagerFmt), Context, extra->hdr, M_FORMAT_MAKEPRINT);
      }
      else if (IsMsgAttach (extra))
      {
	_mutt_make_string (buffer,
			   COLS - 9 < sizeof (buffer) ? COLS - 9: sizeof (buffer),
			   NONULL (PagerFmt), Context, extra->bdy->hdr, M_FORMAT_MAKEPRINT);
      }
      mutt_paddstr (COLS-10, IsHeader (extra) || IsMsgAttach (extra) ?
		    buffer : banner);
      addstr (" -- (");
      if (last_pos < sb.st_size - 1)
	printw ("%d%%)", (int) (100 * last_offset / sb.st_size));
      else
	addstr (topline == 0 ? "all)" : "end)");
      BKGDSET (MT_COLOR_NORMAL);
      SETCOLOR (MT_COLOR_NORMAL);
    }

    if ((redraw & REDRAW_INDEX) && index)
    {
      /* redraw the pager_index indicator, because the
       * flags for this message might have changed. */
      menu_redraw_current (index);

      /* print out the index status bar */
      menu_status_line (buffer, sizeof (buffer), index, NONULL(Status));
 
      move (indexoffset + (option (OPTSTATUSONTOP) ? 0 : (indexlen - 1)), 0);
      SETCOLOR (MT_COLOR_STATUS);
      mutt_paddstr (COLS, buffer);
      SETCOLOR (MT_COLOR_NORMAL);
    }

    redraw = 0;

    move (statusoffset, COLS-1);
    mutt_refresh ();
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

      if (flags & M_PAGER_RETWINCH)
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

	  safe_realloc ((void **)&(lineInfo[i].syntax),
			sizeof (struct syntax_t));
	  if (SearchCompiled && lineInfo[i].search)
	      safe_free ((void **) &(lineInfo[i].search));
	}

	lastLine = 0;
	topline = 0;

	redraw = REDRAW_FULL | REDRAW_SIGWINCH;
	ch = 0;
      }

      SigWinch = 0;
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
	  topline = upNLines (bodylen-PagerContext, lineInfo, topline, hideQuoted);
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
	  topline = upNLines (bodylen/2, lineInfo, topline, hideQuoted);
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_HALF_DOWN:
	if (lineInfo[curline].offset < sb.st_size-1)
	{
	  topline = upNLines (bodylen/2, lineInfo, curline, hideQuoted);
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
	  if ((!SearchBack && ch==OP_SEARCH_NEXT) ||
	      (SearchBack &&ch==OP_SEARCH_OPPOSITE))
	  {
	    /* searching forward */
	    for (i = topline + 1; i < lastLine; i++)
	    {
	      if ((!hideQuoted || lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i < lastLine)
	      topline = i;
	    else
	      mutt_error _("Not found.");
	  }
	  else
	  {
	    /* searching backward */
	    for (i = topline - 1; i >= 0; i--)
	    {
	      if ((!hideQuoted || (has_types && 
		    lineInfo[i].type != MT_COLOR_QUOTED)) && 
		    !lineInfo[i].continuation && lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i >= 0)
	      topline = i;
	    else
	      mutt_error _("Not found.");
	  }

	  if (lineInfo[topline].search_cnt > 0)
	    SearchFlag = M_SEARCH;

	  break;
	}
	/* no previous search pattern, so fall through to search */

      case OP_SEARCH:
      case OP_SEARCH_REVERSE:
	/* leave SearchBack alone if ch == OP_SEARCH_NEXT */
	if (ch == OP_SEARCH)
	  SearchBack = 0;
	else if (ch == OP_SEARCH_REVERSE)
	  SearchBack = 1;

	if (mutt_get_field ((SearchBack ? _("Reverse search: ") :
			  _("Search: ")), searchbuf, sizeof (searchbuf),
			  M_CLEAR) != 0 || !searchbuf[0])
	  break;

	if (SearchCompiled)
	{
	  regfree (&SearchRE);
	  for (i = 0; i < lastLine; i++)
	  {
	    if (lineInfo[i].search)
	      safe_free ((void **) &(lineInfo[i].search));
	    lineInfo[i].search_cnt = -1;
	  }
	}

	if ((err = REGCOMP (&SearchRE, searchbuf, REG_NEWLINE | mutt_which_case (searchbuf))) != 0)
	{
	  regerror (err, &SearchRE, buffer, sizeof (buffer));
	  mutt_error ("%s", buffer);
	  regfree (&SearchRE);
	  for (i = 0; i < maxLine ; i++)
	  {
	    /* cleanup */
	    if (lineInfo[i].search)
	      safe_free ((void **) &(lineInfo[i].search));
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
				&maxLine, M_SEARCH | (flags & M_PAGER_NSKIP),
				&QuoteList, &q_level,
				&force_redraw, &SearchRE) == 0)
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
	    SearchFlag = M_SEARCH;
	}
	redraw = REDRAW_BODY;
	break;

      case OP_SEARCH_TOGGLE:
	if (SearchCompiled)
	{
	  SearchFlag ^= M_SEARCH;
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
	  hideQuoted ^= M_HIDE;
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
			 new_topline, &lastLine, &maxLine, M_TYPES,
			 &QuoteList, &q_level, &force_redraw, &SearchRE))))
		 && lineInfo[new_topline].type != MT_COLOR_QUOTED)
	    new_topline++;

	  if (dretval < 0)
	  {
	    mutt_error _("No more quoted text.");
	    break;
	  }

	  while ((new_topline < lastLine ||
		  (0 == (dretval = display_line (fp, &last_pos, &lineInfo,
			 new_topline, &lastLine, &maxLine, M_TYPES,
			 &QuoteList, &q_level, &force_redraw, &SearchRE))))
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
				&maxLine, has_types, 
				&QuoteList, &q_level, &force_redraw,
				&SearchRE) == 0)
	    i++;
	  topline = upNLines (bodylen, lineInfo, lastLine, hideQuoted);
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
      
      case OP_CREATE_ALIAS:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        if (IsMsgAttach (extra))
	  mutt_create_alias (extra->bdy->hdr->env, NULL);
        else
	  mutt_create_alias (extra->hdr->env, NULL);
	MAYBE_REDRAW (redraw);
	break;

      case OP_DELETE:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
	mutt_set_flag (Context, extra->hdr, M_DELETE, 1);
        if (option (OPTDELETEUNTAG))
	  mutt_set_flag (Context, extra->hdr, M_TAG, 0);
	redraw = REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_DELETE_THREAD:
      case OP_DELETE_SUBTHREAD:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;

	r = mutt_thread_set_flag (extra->hdr, M_DELETE, 1,
				  ch == OP_DELETE_THREAD ? 0 : 1);

	if (r != -1)
	{
	  if (option (OPTDELETEUNTAG))
	    mutt_thread_set_flag (extra->hdr, M_TAG, 0,
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
	  if (flags & M_PAGER_RETWINCH)
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

	    safe_realloc ((void **)&(lineInfo[i].syntax), sizeof (struct syntax_t));
	    if (SearchCompiled && lineInfo[i].search)
		safe_free ((void **) &(lineInfo[i].search));
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
					(has_types ? M_TYPES : 0),
					&QuoteList, &q_level, &force_redraw,
					&SearchRE) == 0)
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

#ifdef USE_POP
	if (Context->magic == M_POP)
	{
	  mutt_flushinp ();
	  mutt_error _("Can't change 'important' flag on POP server.");
	  break;
	}
#endif

	mutt_set_flag (Context, extra->hdr, M_FLAG, !extra->hdr->flagged);
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
	ci_send_message (0, NULL, NULL, NULL, NULL);
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
	CHECK_MODE(IsHeader (extra));
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

#ifdef HAVE_PGP      
      case OP_DECRYPT_SAVE:
#endif
      case OP_SAVE:
	if (IsAttach (extra))
	{
	  mutt_save_attachment_list (extra->fp, 0, extra->bdy, extra->hdr);
	  break;
	}
	/* fall through */
      case OP_COPY_MESSAGE:
      case OP_DECODE_SAVE:
      case OP_DECODE_COPY:
#ifdef HAVE_PGP
      case OP_DECRYPT_COPY:
#endif
	CHECK_MODE(IsHeader (extra));
	if (mutt_save_message (extra->hdr,
#ifdef HAVE_PGP
			       (ch == OP_DECRYPT_SAVE) ||
#endif			       
			       (ch == OP_SAVE) || (ch == OP_DECODE_SAVE),
			       (ch == OP_DECODE_SAVE) || (ch == OP_DECODE_COPY),
#ifdef HAVE_PGP
			       (ch == OP_DECRYPT_SAVE) || (ch == OP_DECRYPT_COPY) ||
#endif
			       0,
			       &redraw) == 0 && (ch == OP_SAVE || ch == OP_DECODE_SAVE
#ifdef HAVE_PGP
						 || ch == OP_DECRYPT_SAVE
#endif
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
	mutt_set_flag (Context, extra->hdr, M_TAG, !extra->hdr->tagged);
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
	if (extra->hdr->read || extra->hdr->old)
	  mutt_set_flag (Context, extra->hdr, M_NEW, 1);
	else if (!first)
	  mutt_set_flag (Context, extra->hdr, M_READ, 1);
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
	mutt_set_flag (Context, extra->hdr, M_DELETE, 0);
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

	r = mutt_thread_set_flag (extra->hdr, M_DELETE, 0,
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

      case OP_VIEW_ATTACHMENTS:
        if (flags & M_PAGER_ATTACHMENT)
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



#ifdef HAVE_PGP
      case OP_FORGET_PASSPHRASE:
	mutt_forget_passphrase ();
	break;

      case OP_MAIL_KEY:
	CHECK_MODE(IsHeader(extra));
        CHECK_ATTACH;
	ci_send_message (SENDKEY, NULL, NULL, extra->ctx, extra->hdr);
	redraw = REDRAW_FULL;
	break;
      
      case OP_EXTRACT_KEYS:
        CHECK_MODE(IsHeader(extra));
        pgp_extract_keys_from_messages(extra->hdr);
        redraw = REDRAW_FULL;
        break;
#endif /* HAVE_PGP */



      default:
	ch = -1;
	break;
    }
  }

  fclose (fp);
  if (IsHeader (extra))
    Context->msgnotreadyet = -1;
    
  cleanup_quote (&QuoteList);
  
  for (i = 0; i < maxLine ; i++)
  {
    safe_free ((void **) &(lineInfo[i].syntax));
    if (SearchCompiled && lineInfo[i].search)
      safe_free ((void **) &(lineInfo[i].search));
  }
  if (SearchCompiled)
  {
    regfree (&SearchRE);
    SearchCompiled = 0;
  }
  safe_free ((void **) &lineInfo);
  if (index)
    mutt_menuDestroy(&index);
  return (rc != -1 ? rc : 0);
}