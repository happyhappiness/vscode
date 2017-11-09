int 
mutt_pager (const char *banner, const char *fname, int flags, pager_t *extra)
{
  static char searchbuf[STRING] = "";
  char buffer[LONG_STRING];
  char helpstr[SHORT_STRING*2];
  char tmphelp[SHORT_STRING*2];
  int i, ch = 0, rc = -1;
  int err, first = 1;
  int r = -1, wrapped = 0, searchctx = 0;

  MUTTMENU *pager_menu = NULL;
  int old_PagerIndexLines;		/* some people want to resize it
  					 * while inside the pager... */

  pager_redraw_data_t rd;

  if (!(flags & MUTT_SHOWCOLOR))
    flags |= MUTT_SHOWFLAT;

  memset (&rd, 0, sizeof (rd));
  rd.banner = banner;
  rd.flags = flags;
  rd.extra = extra;
  rd.indexlen = PagerIndexLines;
  rd.indicator = rd.indexlen / 3;
  rd.helpstr = helpstr;
  rd.searchbuf = searchbuf;
  rd.has_types = (IsHeader(extra) || (flags & MUTT_SHOWCOLOR)) ? MUTT_TYPES : 0; /* main message or rfc822 attachment */

  if ((rd.fp = fopen (fname, "r")) == NULL)
  {
    mutt_perror (fname);
    return (-1);
  }

  if (stat (fname, &rd.sb) != 0)
  {
    mutt_perror (fname);
    safe_fclose (&rd.fp);
    return (-1);
  }
  unlink (fname);

  /* Initialize variables */

  if (IsHeader (extra) && !extra->hdr->read)
  {
    Context->msgnotreadyet = extra->hdr->msgno;
    mutt_set_flag (Context, extra->hdr, MUTT_READ, 1);
  }

  rd.lineInfo = safe_malloc (sizeof (struct line_t) * (rd.maxLine = LINES));
  for (i = 0 ; i < rd.maxLine ; i++)
  {
    memset (&rd.lineInfo[i], 0, sizeof (struct line_t));
    rd.lineInfo[i].type = -1;
    rd.lineInfo[i].search_cnt = -1;
    rd.lineInfo[i].syntax = safe_malloc (sizeof (struct syntax_t));
    (rd.lineInfo[i].syntax)[0].first = (rd.lineInfo[i].syntax)[0].last = -1;
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

  rd.index_status_window = safe_calloc (sizeof (mutt_window_t), 1);
  rd.index_window        = safe_calloc (sizeof (mutt_window_t), 1);
  rd.pager_status_window = safe_calloc (sizeof (mutt_window_t), 1);
  rd.pager_window        = safe_calloc (sizeof (mutt_window_t), 1);

  pager_menu = mutt_new_menu (MENU_PAGER);
  pager_menu->custom_menu_redraw = pager_menu_redraw;
  pager_menu->redraw_data = &rd;
  mutt_push_current_menu (pager_menu);

  while (ch != -1)
  {
    mutt_curs_set (0);

    pager_menu_redraw (pager_menu);

    if (option(OPTBRAILLEFRIENDLY)) {
      if (brailleLine!=-1) {
        move(brailleLine+1, 0);
        brailleLine = -1;
      }
    } else
      mutt_window_move (rd.pager_status_window, 0, rd.pager_status_window->cols-1);

    mutt_refresh ();

    if (IsHeader (extra) && OldHdr == extra->hdr && TopLine != rd.topline
        && rd.lineInfo[rd.curline].offset < rd.sb.st_size-1)
    {
      if (TopLine - rd.topline > rd.lines)
        rd.topline += rd.lines;
      else
        rd.topline = TopLine;
      continue;
    }
    else
      OldHdr = NULL;
      
    ch = km_dokey (MENU_PAGER);
    if (ch >= 0)
      mutt_clear_error ();
    mutt_curs_set (1);

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    if (SigWinch)
    {
      SigWinch = 0;
      mutt_resize_screen ();
      clearok(stdscr,TRUE);/*force complete redraw*/

      if (flags & MUTT_PAGER_RETWINCH)
      {
        /* Store current position. */
        rd.lines = -1;
        for (i = 0; i <= rd.topline; i++)
          if (!rd.lineInfo[i].continuation)
            rd.lines++;

	Resize = safe_malloc (sizeof (struct resize));

	Resize->line = rd.lines;
	Resize->SearchCompiled = rd.SearchCompiled;
	Resize->SearchBack = rd.SearchBack;

	ch = -1;
	rc = OP_REFORMAT_WINCH;
      }
      else
      {
        /* note: mutt_resize_screen() -> mutt_reflow_windows() sets
         * REDRAW_FULL and REDRAW_FLOW */
	ch = 0;
      }
      continue;
    }
#endif
    if (ch < 0)
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
	if (rd.lineInfo[rd.curline].offset < rd.sb.st_size-1)
	{
	  rd.topline = upNLines (PagerContext, rd.lineInfo, rd.curline, rd.hideQuoted);
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
	if (rd.topline != 0)
	{
	  rd.topline = upNLines (rd.pager_window->rows-PagerContext, rd.lineInfo, rd.topline, rd.hideQuoted);
	}
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_NEXT_LINE:
	if (rd.lineInfo[rd.curline].offset < rd.sb.st_size-1)
	{
	  rd.topline++;
	  if (rd.hideQuoted)
	  {
	    while (rd.lineInfo[rd.topline].type == MT_COLOR_QUOTED &&
		   rd.topline < rd.lastLine)
	      rd.topline++;
	  }
	}
	else
	  mutt_error _("Bottom of message is shown.");
	break;

      case OP_PREV_LINE:
	if (rd.topline)
	  rd.topline = upNLines (1, rd.lineInfo, rd.topline, rd.hideQuoted);
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_PAGER_TOP:
        if (rd.topline)
	  rd.topline = 0;
      	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_HALF_UP:
	if (rd.topline)
	  rd.topline = upNLines (rd.pager_window->rows/2, rd.lineInfo, rd.topline, rd.hideQuoted);
	else
	  mutt_error _("Top of message is shown.");
	break;

      case OP_HALF_DOWN:
	if (rd.lineInfo[rd.curline].offset < rd.sb.st_size-1)
	{
	  rd.topline = upNLines (rd.pager_window->rows/2, rd.lineInfo, rd.curline, rd.hideQuoted);
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
	if (rd.SearchCompiled)
	{
	  wrapped = 0;

	  if (SearchContext > 0 && SearchContext < rd.pager_window->rows)
	    searchctx = SearchContext;
	  else
	    searchctx = 0;

search_next:
	  if ((!rd.SearchBack && ch==OP_SEARCH_NEXT) ||
	      (rd.SearchBack &&ch==OP_SEARCH_OPPOSITE))
	  {
	    /* searching forward */
	    for (i = wrapped ? 0 : rd.topline + searchctx + 1; i < rd.lastLine; i++)
	    {
	      if ((!rd.hideQuoted || rd.lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !rd.lineInfo[i].continuation && rd.lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i < rd.lastLine)
	      rd.topline = i;
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
	    for (i = wrapped ? rd.lastLine : rd.topline + searchctx - 1; i >= 0; i--)
	    {
	      if ((!rd.hideQuoted || (rd.has_types && 
		    rd.lineInfo[i].type != MT_COLOR_QUOTED)) && 
		    !rd.lineInfo[i].continuation && rd.lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i >= 0)
	      rd.topline = i;
	    else if (wrapped || !option (OPTWRAPSEARCH))
	      mutt_error _("Not found.");
	    else
	    {
	      mutt_message _("Search wrapped to bottom.");
	      wrapped = 1;
	      goto search_next;
	    }
	  }

	  if (rd.lineInfo[rd.topline].search_cnt > 0)
	  {
	    rd.SearchFlag = MUTT_SEARCH;
	    /* give some context for search results */
	    if (rd.topline - searchctx > 0)
	      rd.topline -= searchctx;
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
	  if (rd.SearchCompiled)
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
	  rd.SearchBack = 0;
	else if (ch == OP_SEARCH_REVERSE)
	  rd.SearchBack = 1;

	if (rd.SearchCompiled)
	{
	  regfree (&rd.SearchRE);
	  for (i = 0; i < rd.lastLine; i++)
	  {
	    if (rd.lineInfo[i].search)
	      FREE (&(rd.lineInfo[i].search));
	    rd.lineInfo[i].search_cnt = -1;
	  }
	}

	if ((err = REGCOMP (&rd.SearchRE, searchbuf, REG_NEWLINE | mutt_which_case (searchbuf))) != 0)
	{
	  regerror (err, &rd.SearchRE, buffer, sizeof (buffer));
	  mutt_error ("%s", buffer);
	  for (i = 0; i < rd.maxLine ; i++)
	  {
	    /* cleanup */
	    if (rd.lineInfo[i].search)
	      FREE (&(rd.lineInfo[i].search));
	    rd.lineInfo[i].search_cnt = -1;
	  }
	  rd.SearchFlag = 0;
	  rd.SearchCompiled = 0;
	}
	else
	{
	  rd.SearchCompiled = 1;
	  /* update the search pointers */
	  i = 0;
	  while (display_line (rd.fp, &rd.last_pos, &rd.lineInfo, i, &rd.lastLine, 
				&rd.maxLine, MUTT_SEARCH | (flags & MUTT_PAGER_NSKIP) | (flags & MUTT_PAGER_NOWRAP),
				&rd.QuoteList, &rd.q_level,
                               &rd.force_redraw, &rd.SearchRE, rd.pager_window) == 0)
	    i++;

	  if (!rd.SearchBack)
	  {
	    /* searching forward */
	    for (i = rd.topline; i < rd.lastLine; i++)
	    {
	      if ((!rd.hideQuoted || rd.lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !rd.lineInfo[i].continuation && rd.lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i < rd.lastLine) rd.topline = i;
	  }
	  else
	  {
	    /* searching backward */
	    for (i = rd.topline; i >= 0; i--)
	    {
	      if ((!rd.hideQuoted || rd.lineInfo[i].type != MT_COLOR_QUOTED) && 
		    !rd.lineInfo[i].continuation && rd.lineInfo[i].search_cnt > 0)
		break;
	    }

	    if (i >= 0) rd.topline = i;
	  }

	  if (rd.lineInfo[rd.topline].search_cnt == 0)
	  {
	    rd.SearchFlag = 0;
	    mutt_error _("Not found.");
	  }
	  else
	  {
	    rd.SearchFlag = MUTT_SEARCH;
	    /* give some context for search results */
	    if (SearchContext > 0 && SearchContext < rd.pager_window->rows)
	      searchctx = SearchContext;
	    else
	      searchctx = 0;
	    if (rd.topline - searchctx > 0)
	      rd.topline -= searchctx;
	  }

	}
	pager_menu->redraw = REDRAW_BODY;
	break;

      case OP_SEARCH_TOGGLE:
	if (rd.SearchCompiled)
	{
	  rd.SearchFlag ^= MUTT_SEARCH;
	  pager_menu->redraw = REDRAW_BODY;
	}
	break;

      case OP_SORT:
      case OP_SORT_REVERSE:
        CHECK_MODE(IsHeader (extra))
        if (mutt_select_sort ((ch == OP_SORT_REVERSE)) == 0)
        {
          set_option (OPTNEEDRESORT);
          ch = -1;
          rc = OP_DISPLAY_MESSAGE;
        }
        break;

      case OP_HELP:
	/* don't let the user enter the help-menu from the help screen! */
	if (! InHelp)
	{
	  InHelp = 1;
	  mutt_help (MENU_PAGER);
	  pager_menu->redraw = REDRAW_FULL;
	  InHelp = 0;
	}
	else
	  mutt_error _("Help is currently being shown.");
	break;

      case OP_PAGER_HIDE_QUOTED:
	if (rd.has_types)
	{
	  rd.hideQuoted ^= MUTT_HIDE;
	  if (rd.hideQuoted && rd.lineInfo[rd.topline].type == MT_COLOR_QUOTED)
	    rd.topline = upNLines (1, rd.lineInfo, rd.topline, rd.hideQuoted);
	  else
	    pager_menu->redraw = REDRAW_BODY;
	}
	break;

      case OP_PAGER_SKIP_QUOTED:
	if (rd.has_types)
	{
	  int dretval = 0;
	  int new_topline = rd.topline;

	  while ((new_topline < rd.lastLine ||
		  (0 == (dretval = display_line (rd.fp, &rd.last_pos, &rd.lineInfo,
			 new_topline, &rd.lastLine, &rd.maxLine, MUTT_TYPES | (flags & MUTT_PAGER_NOWRAP),
                         &rd.QuoteList, &rd.q_level, &rd.force_redraw, &rd.SearchRE, rd.pager_window))))
		 && rd.lineInfo[new_topline].type != MT_COLOR_QUOTED)
	    new_topline++;

	  if (dretval < 0)
	  {
	    mutt_error _("No more quoted text.");
	    break;
	  }

	  while ((new_topline < rd.lastLine ||
		  (0 == (dretval = display_line (rd.fp, &rd.last_pos, &rd.lineInfo,
			 new_topline, &rd.lastLine, &rd.maxLine, MUTT_TYPES | (flags & MUTT_PAGER_NOWRAP),
                         &rd.QuoteList, &rd.q_level, &rd.force_redraw, &rd.SearchRE, rd.pager_window))))
		 && rd.lineInfo[new_topline].type == MT_COLOR_QUOTED)
	    new_topline++;

	  if (dretval < 0)
	  {
	    mutt_error _("No more unquoted text after quoted text.");
	    break;	  
	  }
	  rd.topline = new_topline;
	}
	break;

      case OP_PAGER_BOTTOM: /* move to the end of the file */
	if (rd.lineInfo[rd.curline].offset < rd.sb.st_size - 1)
	{
	  i = rd.curline;
	  /* make sure the types are defined to the end of file */
	  while (display_line (rd.fp, &rd.last_pos, &rd.lineInfo, i, &rd.lastLine, 
				&rd.maxLine, rd.has_types | (flags & MUTT_PAGER_NOWRAP),
				&rd.QuoteList, &rd.q_level, &rd.force_redraw,
                               &rd.SearchRE, rd.pager_window) == 0)
	    i++;
	  rd.topline = upNLines (rd.pager_window->rows, rd.lineInfo, rd.lastLine, rd.hideQuoted);
	}
	else
	  mutt_error _("Bottom of message is shown.");
	break;

      case OP_REDRAW:
	clearok (stdscr, TRUE);
	pager_menu->redraw = REDRAW_FULL;
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
			      extra->actx, extra->bdy);
        else
          ci_bounce_message (extra->hdr);
	break;

      case OP_RESEND:
        CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra))
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_resend (extra->fp, extra->hdr,
			      extra->actx, extra->bdy);
        else
	  mutt_resend_message (NULL, extra->ctx, extra->hdr);
        pager_menu->redraw = REDRAW_FULL;
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
	pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	  pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	    pager_menu->redraw = REDRAW_FULL;
	  else
	    pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	old_PagerIndexLines = PagerIndexLines;

	mutt_enter_command ();

	if (option (OPTNEEDRESORT))
	{
	  unset_option (OPTNEEDRESORT);
	  CHECK_MODE(IsHeader (extra));
	  set_option (OPTNEEDRESORT);
	}

	if (old_PagerIndexLines != PagerIndexLines)
	{
	  if (rd.index)
	    mutt_menuDestroy (&rd.index);
	  rd.index = NULL;
	}

        if ((pager_menu->redraw & REDRAW_FLOW) &&
            (flags & MUTT_PAGER_RETWINCH))
        {
          ch = -1;
          rc = OP_REFORMAT_WINCH;
          continue;
        }

        ch = 0;
	break;

      case OP_FLAG_MESSAGE:
	CHECK_MODE(IsHeader (extra));
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_WRITE, "Cannot flag message");

	mutt_set_flag (Context, extra->hdr, MUTT_FLAG, !extra->hdr->flagged);
	pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
	if (option (OPTRESOLVE))
	{
	  ch = -1;
	  rc = OP_MAIN_NEXT_UNDELETED;
	}
	break;

      case OP_PIPE:
	CHECK_MODE(IsHeader (extra) || IsAttach (extra));
	if (IsAttach (extra))
	  mutt_pipe_attachment_list (extra->actx, extra->fp, 0, extra->bdy, 0);
	else
	  mutt_pipe_message (extra->hdr);
	break;

      case OP_PRINT:
	CHECK_MODE(IsHeader (extra) || IsAttach (extra));
        if (IsAttach (extra))
	  mutt_print_attachment_list (extra->actx, extra->fp, 0, extra->bdy);
        else
	  mutt_print_message (extra->hdr);
	break;

      case OP_MAIL:
	CHECK_MODE(IsHeader (extra) && !IsAttach (extra));
        CHECK_ATTACH;      
	ci_send_message (0, NULL, NULL, extra->ctx, NULL);
	pager_menu->redraw = REDRAW_FULL;
	break;

      case OP_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;      
        if (IsMsgAttach (extra)) 
	  mutt_attach_reply (extra->fp, extra->hdr, extra->actx,
			     extra->bdy, SENDREPLY);
	else
	  ci_send_message (SENDREPLY, NULL, NULL, extra->ctx, extra->hdr);
	pager_menu->redraw = REDRAW_FULL;
	break;

      case OP_RECALL_MESSAGE:
	CHECK_MODE(IsHeader (extra) && !IsAttach(extra));
        CHECK_ATTACH;
	ci_send_message (SENDPOSTPONED, NULL, NULL, extra->ctx, extra->hdr);
	pager_menu->redraw = REDRAW_FULL;
	break;

      case OP_GROUP_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_reply (extra->fp, extra->hdr, extra->actx,
			     extra->bdy, SENDREPLY|SENDGROUPREPLY);
        else
	  ci_send_message (SENDREPLY | SENDGROUPREPLY, NULL, NULL, extra->ctx, extra->hdr);
	pager_menu->redraw = REDRAW_FULL;
	break;

      case OP_LIST_REPLY:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;        
        if (IsMsgAttach (extra))
	  mutt_attach_reply (extra->fp, extra->hdr, extra->actx,
			     extra->bdy, SENDREPLY|SENDLISTREPLY);
        else
	  ci_send_message (SENDREPLY | SENDLISTREPLY, NULL, NULL, extra->ctx, extra->hdr);
	pager_menu->redraw = REDRAW_FULL;
	break;

      case OP_FORWARD_MESSAGE:
	CHECK_MODE(IsHeader (extra) || IsMsgAttach (extra));
        CHECK_ATTACH;
        if (IsMsgAttach (extra))
	  mutt_attach_forward (extra->fp, extra->hdr, extra->actx,
			       extra->bdy);
        else
	  ci_send_message (SENDFORWARD, NULL, NULL, extra->ctx, extra->hdr);
	pager_menu->redraw = REDRAW_FULL;
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
	  mutt_save_attachment_list (extra->actx, extra->fp, 0, extra->bdy, extra->hdr, NULL);
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
			       0) == 0 && (ch == OP_SAVE || ch == OP_DECODE_SAVE
						 || ch == OP_DECRYPT_SAVE
						 ))
	{
	  if (option (OPTRESOLVE))
	  {
	    ch = -1;
	    rc = OP_MAIN_NEXT_UNDELETED;
	  }
	  else
	    pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
	}
	break;

      case OP_SHELL_ESCAPE:
	mutt_shell_escape ();
	break;

      case OP_TAG:
	CHECK_MODE(IsHeader (extra));
	mutt_set_flag (Context, extra->hdr, MUTT_TAG, !extra->hdr->tagged);

	Context->last_tag = extra->hdr->tagged ? extra->hdr :
	  ((Context->last_tag == extra->hdr && !extra->hdr->tagged)
	   ? NULL : Context->last_tag);

	pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	    pager_menu->redraw = REDRAW_FULL;
	  else
	    pager_menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
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
	pager_menu->redraw = REDRAW_FULL;
	break;

     case OP_EDIT_LABEL:
        CHECK_MODE(IsHeader (extra));
        rc = mutt_label_message(extra->hdr);
        if (rc > 0) {
          Context->changed = 1;
          pager_menu->redraw = REDRAW_FULL;
          mutt_message (_("%d labels changed."), rc);
        }
        else {
          mutt_message _("No labels changed.");
        }
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
	pager_menu->redraw = REDRAW_FULL;
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
        pager_menu->redraw = REDRAW_FULL;
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
	break;
#endif

      default:
	ch = -1;
	break;
    }
  }

  safe_fclose (&rd.fp);
  if (IsHeader (extra))
  {
    Context->msgnotreadyet = -1;
    switch (rc)
    {
      case -1:
      case OP_DISPLAY_HEADERS:
        mutt_clear_pager_position ();
        break;
      default:
        TopLine = rd.topline;
        OldHdr = extra->hdr;
        break;
    }
  }
    
  cleanup_quote (&rd.QuoteList);
  
  for (i = 0; i < rd.maxLine ; i++)
  {
    FREE (&(rd.lineInfo[i].syntax));
    if (rd.SearchCompiled && rd.lineInfo[i].search)
      FREE (&(rd.lineInfo[i].search));
  }
  if (rd.SearchCompiled)
  {
    regfree (&rd.SearchRE);
    rd.SearchCompiled = 0;
  }
  FREE (&rd.lineInfo);
  mutt_pop_current_menu (pager_menu);
  mutt_menuDestroy (&pager_menu);
  if (rd.index)
    mutt_menuDestroy(&rd.index);

  FREE (&rd.index_status_window);
  FREE (&rd.index_window);
  FREE (&rd.pager_status_window);
  FREE (&rd.pager_window);

  return (rc != -1 ? rc : 0);
}