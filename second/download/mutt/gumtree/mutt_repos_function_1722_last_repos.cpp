int mutt_index_menu (void)
{
  char buf[LONG_STRING], helpstr[LONG_STRING];
  int op = OP_NULL;
  int done = 0;                /* controls when to exit the "event" loop */
  int i = 0, j;
  int tag = 0;                 /* has the tag-prefix command been pressed? */
  int newcount = -1;
  int oldcount = -1;
  int rc = -1;
  MUTTMENU *menu;
  char *cp;                    /* temporary variable. */
  int index_hint;   /* used to restore cursor position */
  int do_buffy_notify = 1;
  int close = 0; /* did we OP_QUIT or OP_EXIT out of this menu? */
  int attach_msg = option(OPTATTACHMSG);

  menu = mutt_new_menu (MENU_MAIN);
  menu->make_entry = index_make_entry;
  menu->color = index_color;
  menu->current = ci_first_message ();
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_MAIN, IndexHelp);
  menu->custom_menu_redraw = index_menu_redraw;
  mutt_push_current_menu (menu);

  if (!attach_msg)
    mutt_buffy_check(1); /* force the buffy check after we enter the folder */

  FOREVER
  {
    /* Clear the tag prefix unless we just started it.  Don't clear
     * the prefix on a timeout (op==-2), but do clear on an abort (op==-1)
     */
    if (tag && op != OP_TAG_PREFIX && op != OP_TAG_PREFIX_COND && op != -2)
      tag = 0;

    /* check if we need to resort the index because just about
     * any 'op' below could do mutt_enter_command(), either here or
     * from any new menu launched, and change $sort/$sort_aux
     */
    if (option (OPTNEEDRESORT) && Context && Context->msgcount && menu->current >= 0)
      resort_index (menu);

    menu->max = Context ? Context->vcount : 0;
    oldcount = Context ? Context->msgcount : 0;

    if (option (OPTREDRAWTREE) && Context && Context->msgcount && (Sort & SORT_MASK) == SORT_THREADS)
    {
      mutt_draw_tree (Context);
      menu->redraw |= REDRAW_STATUS;
      unset_option (OPTREDRAWTREE);
    }

    if (Context && !attach_msg)
    {
      int check;
      /* check for new mail in the mailbox.  If nonzero, then something has
       * changed about the file (either we got new mail or the file was
       * modified underneath us.)
       */

      index_hint = (Context->vcount && menu->current >= 0 && menu->current < Context->vcount) ? CURHDR->index : 0;

      if ((check = mx_check_mailbox (Context, &index_hint)) < 0)
      {
	if (!Context->path)
	{
	  /* fatal error occurred */
	  FREE (&Context);
	  menu->redraw = REDRAW_FULL;
	}

	set_option (OPTSEARCHINVALID);
      }
      else if (check == MUTT_NEW_MAIL || check == MUTT_REOPENED || check == MUTT_FLAGS)
      {
	update_index (menu, Context, check, oldcount, index_hint);

	/* notify the user of new mail */
	if (check == MUTT_REOPENED)
	  mutt_error _("Mailbox was externally modified.  Flags may be wrong.");
	else if (check == MUTT_NEW_MAIL)
	{
	  mutt_message _("New mail in this mailbox.");
	  if (option (OPTBEEPNEW))
	    beep ();
	} else if (check == MUTT_FLAGS)
	  mutt_message _("Mailbox was externally modified.");

	/* avoid the message being overwritten by buffy */
	do_buffy_notify = 0;

	menu->redraw = REDRAW_FULL;
	menu->max = Context->vcount;

	set_option (OPTSEARCHINVALID);
      }
    }

    if (!attach_msg)
    {
     /* check for new mail in the incoming folders */
     oldcount = newcount;
     if ((newcount = mutt_buffy_check (0)) != oldcount)
       menu->redraw |= REDRAW_STATUS;
     if (do_buffy_notify)
     {
       if (mutt_buffy_notify())
       {
         menu->redraw |= REDRAW_STATUS;
         if (option (OPTBEEPNEW))
           beep();
       }
     }
     else
       do_buffy_notify = 1;
    }

    if (op >= 0)
      mutt_curs_set (0);

    if (menu->menu == MENU_MAIN)
    {
      index_menu_redraw (menu);

      /* give visual indication that the next command is a tag- command */
      if (tag)
      {
        mutt_window_mvaddstr (MuttMessageWindow, 0, 0, "tag-");
        mutt_window_clrtoeol (MuttMessageWindow);
      }

      if (menu->current < menu->max)
        menu->oldcurrent = menu->current;
      else
        menu->oldcurrent = -1;

      if (option (OPTARROWCURSOR))
        mutt_window_move (MuttIndexWindow, menu->current - menu->top + menu->offset, 2);
      else if (option (OPTBRAILLEFRIENDLY))
        mutt_window_move (MuttIndexWindow, menu->current - menu->top + menu->offset, 0);
      else
        mutt_window_move (MuttIndexWindow, menu->current - menu->top + menu->offset,
                          MuttIndexWindow->cols - 1);
      mutt_refresh ();

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      if (SigWinch)
      {
	mutt_flushinp ();
	mutt_resize_screen ();
	SigWinch = 0;
	menu->top = 0; /* so we scroll the right amount */
	/*
	 * force a real complete redraw.  clrtobot() doesn't seem to be able
	 * to handle every case without this.
	 */
	clearok(stdscr,TRUE);
	continue;
      }
#endif

      op = km_dokey (MENU_MAIN);

      dprint(4, (debugfile, "mutt_index_menu[%d]: Got op %d\n", __LINE__, op));

      /* either user abort or timeout */
      if (op < 0)
      {
        if (tag)
          mutt_window_clearline (MuttMessageWindow, 0);
        continue;
      }

      mutt_curs_set (1);

      /* special handling for the tag-prefix function */
      if (op == OP_TAG_PREFIX || op == OP_TAG_PREFIX_COND)
      {
        /* A second tag-prefix command aborts */
        if (tag)
        {
          tag = 0;
          mutt_window_clearline (MuttMessageWindow, 0);
          continue;
        }

	if (!Context)
	{
	  mutt_error _("No mailbox is open.");
	  continue;
	}

	if (!Context->tagged)
	{
          if (op == OP_TAG_PREFIX)
            mutt_error _("No tagged messages.");
          else if (op == OP_TAG_PREFIX_COND)
          {
            mutt_flush_macro_to_endcond ();
            mutt_message  _("Nothing to do.");
          }
	  continue;
	}

        /* get the real command */
        tag = 1;
        continue;
      }
      else if (option (OPTAUTOTAG) && Context && Context->tagged)
	tag = 1;

      mutt_clear_error ();
    }
    else
    {
      if (menu->current < menu->max)
	menu->oldcurrent = menu->current;
      else
	menu->oldcurrent = -1;

      mutt_curs_set (1);	/* fallback from the pager */
    }

    switch (op)
    {

      /* ----------------------------------------------------------------------
       * movement commands
       */

      case OP_BOTTOM_PAGE:
	menu_bottom_page (menu);
	break;
      case OP_FIRST_ENTRY:
	menu_first_entry (menu);
	break;
      case OP_MIDDLE_PAGE:
	menu_middle_page (menu);
	break;
      case OP_HALF_UP:
	menu_half_up (menu);
	break;
      case OP_HALF_DOWN:
	menu_half_down (menu);
	break;
      case OP_NEXT_LINE:
	menu_next_line (menu);
	break;
      case OP_PREV_LINE:
	menu_prev_line (menu);
	break;
      case OP_NEXT_PAGE:
	menu_next_page (menu);
	break;
      case OP_PREV_PAGE:
	menu_prev_page (menu);
	break;
      case OP_LAST_ENTRY:
	menu_last_entry (menu);
	break;
      case OP_TOP_PAGE:
	menu_top_page (menu);
	break;
      case OP_CURRENT_TOP:
	menu_current_top (menu);
	break;
      case OP_CURRENT_MIDDLE:
	menu_current_middle (menu);
	break;
      case OP_CURRENT_BOTTOM:
	menu_current_bottom (menu);
	break;

      case OP_JUMP:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        if (isdigit (LastKey)) mutt_unget_event (LastKey, 0);
	buf[0] = 0;
	if (mutt_get_field (_("Jump to message: "), buf, sizeof (buf), 0) != 0
	    || !buf[0])
        {
          if (menu->menu == MENU_PAGER)
          {
            op = OP_DISPLAY_MESSAGE;
            continue;
          }
	  break;
        }

	if (mutt_atoi (buf, &i) < 0)
	{
	  mutt_error _("Argument must be a message number.");
	  break;
	}

	if (i > 0 && i <= Context->msgcount)
	{
	  for (j = i-1; j < Context->msgcount; j++)
	  {
	    if (Context->hdrs[j]->virtual != -1)
	      break;
	  }
	  if (j >= Context->msgcount)
	  {
	    for (j = i-2; j >= 0; j--)
	    {
	      if (Context->hdrs[j]->virtual != -1)
		break;
	    }
	  }

	  if (j >= 0)
	  {
	    menu->current = Context->hdrs[j]->virtual;
	    if (menu->menu == MENU_PAGER)
	    {
	      op = OP_DISPLAY_MESSAGE;
	      continue;
	    }
	    else
	    menu->redraw = REDRAW_MOTION;
	  }
	  else
	    mutt_error _("That message is not visible.");
	}
	else
	  mutt_error _("Invalid message number.");

	break;

	/* --------------------------------------------------------------------
	 * `index' specific commands
	 */

      case OP_MAIN_DELETE_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot delete message(s)"));

	CHECK_ATTACH;
	mutt_pattern_func (MUTT_DELETE, _("Delete messages matching: "));
	menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	break;

#ifdef USE_POP
      case OP_MAIN_FETCH_MAIL:

	CHECK_ATTACH;
	pop_fetch_mail ();
	menu->redraw = REDRAW_FULL;
	break;
#endif /* USE_POP */

      case OP_HELP:

	mutt_help (MENU_MAIN);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_MAIN_SHOW_LIMIT:
	CHECK_IN_MAILBOX;
	if (!Context->pattern)
	   mutt_message _("No limit pattern is in effect.");
	else
	{
	   char buf[STRING];
	   /* L10N: ask for a limit to apply */
	   snprintf (buf, sizeof(buf), _("Limit: %s"),Context->pattern);
           mutt_message ("%s", buf);
	}
        break;

      case OP_MAIN_LIMIT:

	CHECK_IN_MAILBOX;
	menu->oldcurrent = (Context->vcount && menu->current >= 0 && menu->current < Context->vcount) ?
		CURHDR->index : -1;
	if (mutt_pattern_func (MUTT_LIMIT, _("Limit to messages matching: ")) == 0)
	{
	  if (menu->oldcurrent >= 0)
	  {
	    /* try to find what used to be the current message */
	    menu->current = -1;
	    for (i = 0; i < Context->vcount; i++)
	      if (Context->hdrs[Context->v2r[i]]->index == menu->oldcurrent)
	      {
		menu->current = i;
		break;
	      }
	    if (menu->current < 0) menu->current = 0;
	  }
	  else
	    menu->current = 0;
	  if (Context->msgcount && (Sort & SORT_MASK) == SORT_THREADS)
	    mutt_draw_tree (Context);
	  menu->redraw = REDRAW_FULL;
	}
        if (Context->pattern)
	  mutt_message _("To view all messages, limit to \"all\".");
	break;

      case OP_QUIT:

	close = op;
	if (attach_msg)
	{
	 done = 1;
	 break;
	}

	if (query_quadoption (OPT_QUIT, _("Quit Mutt?")) == MUTT_YES)
	{
	  int check;

	  oldcount = Context ? Context->msgcount : 0;

	  if (!Context || (check = mx_close_mailbox (Context, &index_hint)) == 0)
	    done = 1;
	  else
	  {
	    if (check == MUTT_NEW_MAIL || check == MUTT_REOPENED)
	      update_index (menu, Context, check, oldcount, index_hint);

	    menu->redraw = REDRAW_FULL; /* new mail arrived? */
	    set_option (OPTSEARCHINVALID);
	  }
	}
	break;

      case OP_REDRAW:

	clearok (stdscr, TRUE);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_SEARCH:
      case OP_SEARCH_REVERSE:
      case OP_SEARCH_NEXT:
      case OP_SEARCH_OPPOSITE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if ((menu->current = mutt_search_command (menu->current, op)) == -1)
	  menu->current = menu->oldcurrent;
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_SORT:
      case OP_SORT_REVERSE:

	if (mutt_select_sort ((op == OP_SORT_REVERSE)) == 0)
	{
	  if (Context && Context->msgcount)
	  {
	    resort_index (menu);
	    set_option (OPTSEARCHINVALID);
	  }
	  if (menu->menu == MENU_PAGER)
	  {
	    op = OP_DISPLAY_MESSAGE;
	    continue;
	  }
	  menu->redraw |= REDRAW_STATUS;
	}
	break;

      case OP_TAG:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (tag && !option (OPTAUTOTAG))
	{
	  for (j = 0; j < Context->vcount; j++)
	    mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], MUTT_TAG, 0);
	  menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, MUTT_TAG, !CURHDR->tagged);

	  Context->last_tag = CURHDR->tagged ? CURHDR :
	    ((Context->last_tag == CURHDR && !CURHDR->tagged)
	     ? NULL : Context->last_tag);

	  menu->redraw |= REDRAW_STATUS;
	  if (option (OPTRESOLVE) && menu->current < Context->vcount - 1)
	  {
	    menu->current++;
	    menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	break;

      case OP_MAIN_TAG_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_pattern_func (MUTT_TAG, _("Tag messages matching: "));
	menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	break;

      case OP_MAIN_UNDELETE_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot undelete message(s)"));

	if (mutt_pattern_func (MUTT_UNDELETE, _("Undelete messages matching: ")) == 0)
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	break;

      case OP_MAIN_UNTAG_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (mutt_pattern_func (MUTT_UNTAG, _("Untag messages matching: ")) == 0)
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	break;

	/* --------------------------------------------------------------------
	 * The following operations can be performed inside of the pager.
	 */

#ifdef USE_IMAP
      case OP_MAIN_IMAP_FETCH:
	if (Context && Context->magic == MUTT_IMAP)
	  imap_check_mailbox (Context, &index_hint, 1);
        break;

      case OP_MAIN_IMAP_LOGOUT_ALL:
	if (Context && Context->magic == MUTT_IMAP)
	{
	  if (mx_close_mailbox (Context, &index_hint) != 0)
	  {
	    set_option (OPTSEARCHINVALID);
	    menu->redraw = REDRAW_FULL;
	    break;
	  }
	  FREE (&Context);
	}
	imap_logout_all();
	mutt_message _("Logged out of IMAP servers.");
	set_option (OPTSEARCHINVALID);
	menu->redraw = REDRAW_FULL;
	break;
#endif

      case OP_MAIN_SYNC_FOLDER:

	if (Context && !Context->msgcount)
	  break;

	CHECK_MSGCOUNT;
	CHECK_READONLY;
	{
	  int oldvcount = Context->vcount;
	  int oldcount  = Context->msgcount;
	  int check, newidx;
	  HEADER *newhdr = NULL;

	  /* don't attempt to move the cursor if there are no visible messages in the current limit */
	  if (menu->current < Context->vcount)
	  {
	    /* threads may be reordered, so figure out what header the cursor
	     * should be on. #3092 */
	    newidx = menu->current;
	    if (CURHDR->deleted)
	      newidx = ci_next_undeleted (menu->current);
	    if (newidx < 0)
	      newidx = ci_previous_undeleted (menu->current);
	    if (newidx >= 0)
	      newhdr = Context->hdrs[Context->v2r[newidx]];
	  }

	  if ((check = mx_sync_mailbox (Context, &index_hint)) == 0)
	  {
	    if (newhdr && Context->vcount != oldvcount)
	      for (j = 0; j < Context->vcount; j++)
	      {
		if (Context->hdrs[Context->v2r[j]] == newhdr)
		{
		  menu->current = j;
		  break;
		}
	      }
	    set_option (OPTSEARCHINVALID);
	  }
	  else if (check == MUTT_NEW_MAIL || check == MUTT_REOPENED)
	    update_index (menu, Context, check, oldcount, index_hint);

	  /*
	   * do a sanity check even if mx_sync_mailbox failed.
	   */

	  if (menu->current < 0 || menu->current >= Context->vcount)
	    menu->current = ci_first_message ();
	}

	/* check for a fatal error, or all messages deleted */
	if (!Context->path)
	  FREE (&Context);

	/* if we were in the pager, redisplay the message */
	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
        else
	  menu->redraw = REDRAW_FULL;
	break;

#ifdef USE_SIDEBAR
      case OP_SIDEBAR_OPEN:
#endif
      case OP_MAIN_CHANGE_FOLDER:
      case OP_MAIN_NEXT_UNREAD_MAILBOX:

	if (attach_msg)
	  op = OP_MAIN_CHANGE_FOLDER_READONLY;

	/* fallback to the readonly case */

      case OP_MAIN_CHANGE_FOLDER_READONLY:

        if ((op == OP_MAIN_CHANGE_FOLDER_READONLY) || option (OPTREADONLY))
          cp = _("Open mailbox in read-only mode");
        else
          cp = _("Open mailbox");

	buf[0] = '\0';
	if ((op == OP_MAIN_NEXT_UNREAD_MAILBOX) && Context && Context->path)
	{
	  strfcpy (buf, Context->path, sizeof (buf));
	  mutt_pretty_mailbox (buf, sizeof (buf));
	  mutt_buffy (buf, sizeof (buf));
	  if (!buf[0])
	  {
	    mutt_error _("No mailboxes have new mail");
	    break;
	  }
	}
#ifdef USE_SIDEBAR
        else if (op == OP_SIDEBAR_OPEN)
        {
          const char *path = mutt_sb_get_highlight();
          if (!path || !*path)
            break;
          strncpy (buf, path, sizeof (buf));
        }
#endif
	else
	{
	  mutt_buffy (buf, sizeof (buf));

          if (mutt_enter_fname (cp, buf, sizeof (buf), 1) == -1)
          {
            if (menu->menu == MENU_PAGER)
            {
              op = OP_DISPLAY_MESSAGE;
              continue;
            }
            else
              break;
          }
	  if (!buf[0])
	  {
            mutt_window_clearline (MuttMessageWindow, 0);
	    break;
	  }
	}

	mutt_expand_path (buf, sizeof (buf));
	if (mx_get_magic (buf) <= 0)
	{
	  mutt_error (_("%s is not a mailbox."), buf);
	  break;
	}

	/* keepalive failure in mutt_enter_fname may kill connection. #3028 */
	if (Context && !Context->path)
	  FREE (&Context);

        if (Context)
        {
	  int check;
          char *new_last_folder;

#ifdef USE_COMPRESSED
	  if (Context->compress_info && Context->realpath)
	    new_last_folder = safe_strdup (Context->realpath);
	  else
#endif
	  new_last_folder = safe_strdup (Context->path);
	  oldcount = Context ? Context->msgcount : 0;

	  if ((check = mx_close_mailbox (Context, &index_hint)) != 0)
	  {
	    if (check == MUTT_NEW_MAIL || check == MUTT_REOPENED)
	      update_index (menu, Context, check, oldcount, index_hint);

            FREE (&new_last_folder);
	    set_option (OPTSEARCHINVALID);
	    menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	    break;
	  }
	  FREE (&Context);
          FREE (&LastFolder);
          LastFolder = new_last_folder;
	}
	mutt_str_replace (&CurrentFolder, buf);

        mutt_sleep (0);

        /* Note that menu->menu may be MENU_PAGER if the change folder
         * operation originated from the pager.
         *
         * However, exec commands currently use CurrentMenu to determine what
         * functions are available, which is automatically set by the
         * mutt_push/pop_current_menu() functions.  If that changes, the menu
         * would need to be reset here, and the pager cleanup code after the
         * switch statement would need to be run. */
	mutt_folder_hook (buf);

	if ((Context = mx_open_mailbox (buf,
					(option (OPTREADONLY) || op == OP_MAIN_CHANGE_FOLDER_READONLY) ?
					MUTT_READONLY : 0, NULL)) != NULL)
	{
	  menu->current = ci_first_message ();
	}
	else
	  menu->current = 0;

#ifdef USE_SIDEBAR
        mutt_sb_set_open_buffy ();
#endif

	mutt_clear_error ();
	mutt_buffy_check(1); /* force the buffy check after we have changed
			      the folder */
	menu->redraw = REDRAW_FULL;
	set_option (OPTSEARCHINVALID);
	break;

      case OP_DISPLAY_MESSAGE:
      case OP_DISPLAY_HEADERS: /* don't weed the headers */

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	/*
	 * toggle the weeding of headers so that a user can press the key
	 * again while reading the message.
	 */
	if (op == OP_DISPLAY_HEADERS)
	  toggle_option (OPTWEED);

	unset_option (OPTNEEDRESORT);

	if ((Sort & SORT_MASK) == SORT_THREADS && CURHDR->collapsed)
	{
	  mutt_uncollapse_thread (Context, CURHDR);
	  mutt_set_virtual (Context);
	  if (option (OPTUNCOLLAPSEJUMP))
	    menu->current = mutt_thread_next_unread (Context, CURHDR);
	}

	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);

        /* If we are returning to the pager via an index menu redirection, we
         * need to reset the menu->menu.  Otherwise mutt_pop_current_menu() will
         * set CurrentMenu incorrectly when we return back to the index menu. */
        menu->menu = MENU_MAIN;

        if ((op = mutt_display_message (CURHDR)) < 0)
	{
	  unset_option (OPTNEEDRESORT);
	  break;
	}

        /* This is used to redirect a single operation back here afterwards.  If
         * mutt_display_message() returns 0, then the menu and pager state will
         * be cleaned up after this switch statement. */
	menu->menu = MENU_PAGER;
 	menu->oldcurrent = menu->current;
	continue;

      case OP_EXIT:

	close = op;
	if (menu->menu == MENU_MAIN && attach_msg)
	{
	 done = 1;
	 break;
	}

	if ((menu->menu == MENU_MAIN)
	    && (query_quadoption (OPT_QUIT,
				  _("Exit Mutt without saving?")) == MUTT_YES))
	{
	  if (Context)
	  {
	    mx_fastclose_mailbox (Context);
	    FREE (&Context);
	  }
	  done = 1;
	}
	break;

      case OP_MAIN_BREAK_THREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;

        if ((Sort & SORT_MASK) != SORT_THREADS)
	  mutt_error _("Threading is not enabled.");
	else if (CURHDR->env->in_reply_to || CURHDR->env->references)
	{
	  {
	    HEADER *oldcur = CURHDR;

	    mutt_break_thread (CURHDR);
	    mutt_sort_headers (Context, 1);
	    menu->current = oldcur->virtual;
	  }

	  Context->changed = 1;
	  mutt_message _("Thread broken");

	  if (menu->menu == MENU_PAGER)
	  {
	    op = OP_DISPLAY_MESSAGE;
	    continue;
	  }
	  else
	    menu->redraw |= REDRAW_INDEX;
	}
	else
	  mutt_error _("Thread cannot be broken, message is not part of a thread");

	break;

      case OP_MAIN_LINK_THREADS:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot link threads"));

        if ((Sort & SORT_MASK) != SORT_THREADS)
	  mutt_error _("Threading is not enabled.");
	else if (!CURHDR->env->message_id)
	  mutt_error _("No Message-ID: header available to link thread");
	else if (!tag && (!Context->last_tag || !Context->last_tag->tagged))
	  mutt_error _("First, please tag a message to be linked here");
	else
	{
	  HEADER *oldcur = CURHDR;

	  if (mutt_link_threads (CURHDR, tag ? NULL : Context->last_tag,
				 Context))
	  {
	    mutt_sort_headers (Context, 1);
	    menu->current = oldcur->virtual;

	    Context->changed = 1;
	    mutt_message _("Threads linked");
	  }
	  else
	    mutt_error _("No thread linked");
	}

	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;

	break;

      case OP_EDIT_TYPE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_ATTACH;
	mutt_edit_content_type (CURHDR, CURHDR->content, NULL);
	/* if we were in the pager, redisplay the message */
	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
        else
	  menu->redraw = REDRAW_CURRENT;
	break;

      case OP_MAIN_NEXT_UNDELETED:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (menu->current >= Context->vcount - 1)
	{
	  if (menu->menu == MENU_MAIN)
	    mutt_error _("You are on the last message.");
	  break;
	}
	if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	{
	  menu->current = menu->oldcurrent;
	  if (menu->menu == MENU_MAIN)
	    mutt_error _("No undeleted messages.");
	}
	else if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_NEXT_ENTRY:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (menu->current >= Context->vcount - 1)
	{
	  if (menu->menu == MENU_MAIN)
	    mutt_error _("You are on the last message.");
	  break;
	}
	menu->current++;
	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_MAIN_PREV_UNDELETED:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (menu->current < 1)
	{
	  mutt_error _("You are on the first message.");
	  break;
	}
	if ((menu->current = ci_previous_undeleted (menu->current)) == -1)
	{
	  menu->current = menu->oldcurrent;
	  if (menu->menu == MENU_MAIN)
	    mutt_error _("No undeleted messages.");
	}
	else if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_PREV_ENTRY:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (menu->current < 1)
	{
	  if (menu->menu == MENU_MAIN) mutt_error _("You are on the first message.");
	  break;
	}
	menu->current--;
	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_DECRYPT_COPY:
      case OP_DECRYPT_SAVE:
        if (!WithCrypto)
          break;
        /* fall thru */
      case OP_COPY_MESSAGE:
      case OP_SAVE:
      case OP_DECODE_COPY:
      case OP_DECODE_SAVE:
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        if (mutt_save_message (tag ? NULL : CURHDR,
			       (op == OP_DECRYPT_SAVE) ||
			       (op == OP_SAVE) || (op == OP_DECODE_SAVE),
			       (op == OP_DECODE_SAVE) || (op == OP_DECODE_COPY),
			       (op == OP_DECRYPT_SAVE) || (op == OP_DECRYPT_COPY) ||
			       0) == 0 &&
	     (op == OP_SAVE || op == OP_DECODE_SAVE || op == OP_DECRYPT_SAVE)
	    )
	{
          menu->redraw |= REDRAW_STATUS;
	  if (tag)
	    menu->redraw |= REDRAW_INDEX;
	  else if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw |= REDRAW_CURRENT;
	    }
	    else
	      menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	break;

      case OP_MAIN_NEXT_NEW:
      case OP_MAIN_NEXT_UNREAD:
      case OP_MAIN_PREV_NEW:
      case OP_MAIN_PREV_UNREAD:
      case OP_MAIN_NEXT_NEW_THEN_UNREAD:
      case OP_MAIN_PREV_NEW_THEN_UNREAD:

      {
	int first_unread = -1;
	int first_new    = -1;

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;

	i = menu->current;
	menu->current = -1;
	for (j = 0; j != Context->vcount; j++)
	{
#define CURHDRi Context->hdrs[Context->v2r[i]]
	  if (op == OP_MAIN_NEXT_NEW || op == OP_MAIN_NEXT_UNREAD || op == OP_MAIN_NEXT_NEW_THEN_UNREAD)
	  {
	    i++;
	    if (i > Context->vcount - 1)
	    {
	      mutt_message _("Search wrapped to top.");
	      i = 0;
	    }
	  }
	  else
	  {
	    i--;
	    if (i < 0)
	    {
	      mutt_message _("Search wrapped to bottom.");
	      i = Context->vcount - 1;
	    }
	  }

	  if (CURHDRi->collapsed && (Sort & SORT_MASK) == SORT_THREADS)
	  {
	    if (UNREAD (CURHDRi) && first_unread == -1)
	      first_unread = i;
	    if (UNREAD (CURHDRi) == 1 && first_new == -1)
	      first_new = i;
	  }
	  else if ((!CURHDRi->deleted && !CURHDRi->read))
	  {
	    if (first_unread == -1)
	      first_unread = i;
	    if ((!CURHDRi->old) && first_new == -1)
	      first_new = i;
	  }

	  if ((op == OP_MAIN_NEXT_UNREAD || op == OP_MAIN_PREV_UNREAD) &&
	      first_unread != -1)
	    break;
	  if ((op == OP_MAIN_NEXT_NEW || op == OP_MAIN_PREV_NEW ||
	       op == OP_MAIN_NEXT_NEW_THEN_UNREAD || op == OP_MAIN_PREV_NEW_THEN_UNREAD)
	      && first_new != -1)
	    break;
	}
#undef CURHDRi
	if ((op == OP_MAIN_NEXT_NEW || op == OP_MAIN_PREV_NEW ||
	     op == OP_MAIN_NEXT_NEW_THEN_UNREAD || op == OP_MAIN_PREV_NEW_THEN_UNREAD)
	    && first_new != -1)
	  menu->current = first_new;
	else if ((op == OP_MAIN_NEXT_UNREAD || op == OP_MAIN_PREV_UNREAD ||
		  op == OP_MAIN_NEXT_NEW_THEN_UNREAD || op == OP_MAIN_PREV_NEW_THEN_UNREAD)
		 && first_unread != -1)
	  menu->current = first_unread;

	if (menu->current == -1)
	{
	  menu->current = menu->oldcurrent;
	  if (op == OP_MAIN_NEXT_NEW || op == OP_MAIN_PREV_NEW)
          {
            if (Context->pattern)
              mutt_error (_("No new messages in this limited view."));
            else
              mutt_error (_("No new messages."));
          }
          else
          {
            if (Context->pattern)
              mutt_error (_("No unread messages in this limited view."));
            else
              mutt_error (_("No unread messages."));
          }
	}
	else if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;
      }
      case OP_FLAG_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_WRITE, _("Cannot flag message"));

        if (tag)
        {
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->tagged)
	      mutt_set_flag (Context, Context->hdrs[Context->v2r[j]],
			     MUTT_FLAG, !Context->hdrs[Context->v2r[j]]->flagged);
	  }

	  menu->redraw |= REDRAW_INDEX;
	}
        else
        {
	  mutt_set_flag (Context, CURHDR, MUTT_FLAG, !CURHDR->flagged);
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw |= REDRAW_CURRENT;
	    }
	    else
	      menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_TOGGLE_NEW:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_SEEN, _("Cannot toggle new"));

	if (tag)
	{
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->tagged)
	    {
	      if (Context->hdrs[Context->v2r[j]]->read ||
		  Context->hdrs[Context->v2r[j]]->old)
		mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], MUTT_NEW, 1);
	      else
		mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], MUTT_READ, 1);
	    }
	  }
	  menu->redraw |= REDRAW_STATUS | REDRAW_INDEX;
	}
	else
	{
	  if (CURHDR->read || CURHDR->old)
	    mutt_set_flag (Context, CURHDR, MUTT_NEW, 1);
	  else
	    mutt_set_flag (Context, CURHDR, MUTT_READ, 1);

	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw |= REDRAW_CURRENT;
	    }
	    else
	      menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	  menu->redraw |= REDRAW_STATUS;
	}
	break;

      case OP_TOGGLE_WRITE:

	CHECK_IN_MAILBOX;
	if (mx_toggle_write (Context) == 0)
	  menu->redraw |= REDRAW_STATUS;
	break;

      case OP_MAIN_NEXT_THREAD:
      case OP_MAIN_NEXT_SUBTHREAD:
      case OP_MAIN_PREV_THREAD:
      case OP_MAIN_PREV_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	switch (op)
	{
	  case OP_MAIN_NEXT_THREAD:
	    menu->current = mutt_next_thread (CURHDR);
	    break;

	  case OP_MAIN_NEXT_SUBTHREAD:
	    menu->current = mutt_next_subthread (CURHDR);
	    break;

	  case OP_MAIN_PREV_THREAD:
	    menu->current = mutt_previous_thread (CURHDR);
	    break;

	  case OP_MAIN_PREV_SUBTHREAD:
	    menu->current = mutt_previous_subthread (CURHDR);
	    break;
	}

	if (menu->current < 0)
	{
	  menu->current = menu->oldcurrent;
	  if (op == OP_MAIN_NEXT_THREAD || op == OP_MAIN_NEXT_SUBTHREAD)
	    mutt_error _("No more threads.");
	  else
	    mutt_error _("You are on the first thread.");
	}
	else if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_MAIN_ROOT_MESSAGE:
      case OP_MAIN_PARENT_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;

	if ((menu->current = mutt_parent_message (Context, CURHDR,
                                                  op == OP_MAIN_ROOT_MESSAGE)) < 0)
	{
	  menu->current = menu->oldcurrent;
	}
	else if (menu->menu == MENU_PAGER)
        {
          op = OP_DISPLAY_MESSAGE;
          continue;
        }
        else
          menu->redraw = REDRAW_MOTION;
	break;

      case OP_MAIN_SET_FLAG:
      case OP_MAIN_CLEAR_FLAG:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	/* CHECK_ACL(MUTT_ACL_WRITE); */

	if (mutt_change_flag (tag ? NULL : CURHDR, (op == OP_MAIN_SET_FLAG)) == 0)
	{
	  menu->redraw |= REDRAW_STATUS;
	  if (tag)
	    menu->redraw |= REDRAW_INDEX;
	  else if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw |= REDRAW_CURRENT;
	    }
	    else
	      menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	break;

      case OP_MAIN_COLLAPSE_THREAD:
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;

        if ((Sort & SORT_MASK) != SORT_THREADS)
        {
	  mutt_error _("Threading is not enabled.");
	  break;
	}

	if (CURHDR->collapsed)
	{
	  menu->current = mutt_uncollapse_thread (Context, CURHDR);
	  mutt_set_virtual (Context);
	  if (option (OPTUNCOLLAPSEJUMP))
	    menu->current = mutt_thread_next_unread (Context, CURHDR);
	}
	else if (option (OPTCOLLAPSEUNREAD) || !UNREAD (CURHDR))
	{
	  menu->current = mutt_collapse_thread (Context, CURHDR);
	  mutt_set_virtual (Context);
	}
	else
	{
	  mutt_error _("Thread contains unread messages.");
	  break;
	}

	menu->redraw = REDRAW_INDEX | REDRAW_STATUS;

       break;

      case OP_MAIN_COLLAPSE_ALL:
        CHECK_MSGCOUNT;
        CHECK_VISIBLE;

        if ((Sort & SORT_MASK) != SORT_THREADS)
        {
	  mutt_error _("Threading is not enabled.");
	  break;
	}

        {
	  HEADER *h, *base;
	  THREAD *thread, *top;
	  int final;

	  if (CURHDR->collapsed)
	    final = mutt_uncollapse_thread (Context, CURHDR);
	  else if (option (OPTCOLLAPSEUNREAD) || !UNREAD (CURHDR))
	    final = mutt_collapse_thread (Context, CURHDR);
	  else
	    final = CURHDR->virtual;

	  base = Context->hdrs[Context->v2r[final]];

	  top = Context->tree;
	  Context->collapsed = !Context->collapsed;
	  while ((thread = top) != NULL)
	  {
	    while (!thread->message)
	      thread = thread->child;
	    h = thread->message;

	    if (h->collapsed != Context->collapsed)
	    {
	      if (h->collapsed)
		mutt_uncollapse_thread (Context, h);
	      else if (option (OPTCOLLAPSEUNREAD) || !UNREAD (h))
		mutt_collapse_thread (Context, h);
	    }
	    top = top->next;
	  }

	  mutt_set_virtual (Context);
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->index == base->index)
	    {
	      menu->current = j;
	      break;
	    }
	  }

	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      /* --------------------------------------------------------------------
       * These functions are invoked directly from the internal-pager
       */

      case OP_BOUNCE_MESSAGE:

	CHECK_ATTACH;
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	ci_bounce_message (tag ? NULL : CURHDR);
	break;

      case OP_CREATE_ALIAS:

        mutt_create_alias (Context && Context->vcount ? CURHDR->env : NULL, NULL);
        menu->redraw |= REDRAW_CURRENT;
	break;

      case OP_QUERY:
	CHECK_ATTACH;
	mutt_query_menu (NULL, 0);
	break;

      case OP_PURGE_MESSAGE:
      case OP_DELETE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot delete message"));

	if (tag)
	{
	  mutt_tag_set_flag (MUTT_DELETE, 1);
          mutt_tag_set_flag (MUTT_PURGE, (op == OP_PURGE_MESSAGE));
	  if (option (OPTDELETEUNTAG))
	    mutt_tag_set_flag (MUTT_TAG, 0);
	  menu->redraw |= REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, MUTT_DELETE, 1);
	  mutt_set_flag (Context, CURHDR, MUTT_PURGE, (op == OP_PURGE_MESSAGE));
	  if (option (OPTDELETEUNTAG))
	    mutt_set_flag (Context, CURHDR, MUTT_TAG, 0);
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw |= REDRAW_CURRENT;
	    }
	    else if (menu->menu == MENU_PAGER)
	    {
	      op = OP_DISPLAY_MESSAGE;
	      continue;
	    }
	    else
	      menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_DELETE_THREAD:
      case OP_DELETE_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot delete message(s)"));

	rc = mutt_thread_set_flag (CURHDR, MUTT_DELETE, 1,
				   op == OP_DELETE_THREAD ? 0 : 1);

	if (rc != -1)
	{
	  if (option (OPTDELETEUNTAG))
	    mutt_thread_set_flag (CURHDR, MUTT_TAG, 0,
				  op == OP_DELETE_THREAD ? 0 : 1);
	  if (option (OPTRESOLVE))
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	      menu->current = menu->oldcurrent;
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_DISPLAY_ADDRESS:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_display_address (CURHDR->env);
	break;

      case OP_ENTER_COMMAND:

	mutt_enter_command ();
	mutt_check_rescore (Context);
	break;

      case OP_EDIT_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	CHECK_ATTACH;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_INSERT, _("Cannot edit message"));

	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
        mutt_edit_message (Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;

	break;

      case OP_FORWARD_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_ATTACH;
	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
	ci_send_message (SENDFORWARD, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;


      case OP_FORGET_PASSPHRASE:
	crypt_forget_passphrase ();
	break;

      case OP_GROUP_REPLY:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_ATTACH;
	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
	ci_send_message (SENDREPLY|SENDGROUPREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_EDIT_LABEL:

	CHECK_MSGCOUNT;
	CHECK_READONLY;
	rc = mutt_label_message(tag ? NULL : CURHDR);
	if (rc > 0) {
	  Context->changed = 1;
	  menu->redraw = REDRAW_FULL;
          /* L10N: This is displayed when the x-label on one or more
           * messages is edited. */
	  mutt_message (_("%d labels changed."), rc);
	}
	else {
          /* L10N: This is displayed when editing an x-label, but no messages
           * were updated.  Possibly due to canceling at the prompt or if the new
           * label is the same as the old label. */
	  mutt_message _("No labels changed.");
	}
	break;

      case OP_LIST_REPLY:

	CHECK_ATTACH;
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
	ci_send_message (SENDREPLY|SENDLISTREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_MAIL:

	CHECK_ATTACH;
	ci_send_message (0, NULL, NULL, Context, NULL);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_MAIL_KEY:
        if (!(WithCrypto & APPLICATION_PGP))
          break;
	CHECK_ATTACH;
	ci_send_message (SENDKEY, NULL, NULL, NULL, NULL);
	menu->redraw = REDRAW_FULL;
	break;


      case OP_EXTRACT_KEYS:
        if (!WithCrypto)
          break;
        CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        crypt_extract_keys_from_messages(tag ? NULL : CURHDR);
        menu->redraw = REDRAW_FULL;
        break;


      case OP_CHECK_TRADITIONAL:
        if (!(WithCrypto & APPLICATION_PGP))
          break;
        CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        if (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);

        if (menu->menu == MENU_PAGER)
        {
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
        break;

      case OP_PIPE:

	CHECK_MSGCOUNT;
	CHECK_VISIBLE;
	mutt_pipe_message (tag ? NULL : CURHDR);

#ifdef USE_IMAP
	/* in an IMAP folder index with imap_peek=no, piping could change
	 * new or old messages status to read. Redraw what's needed.
	 */
	if (Context->magic == MUTT_IMAP && !option (OPTIMAPPEEK))
	{
	  menu->redraw |= (tag ? REDRAW_INDEX : REDRAW_CURRENT) | REDRAW_STATUS;
	}
#endif

	break;

      case OP_PRINT:

	CHECK_MSGCOUNT;
	CHECK_VISIBLE;
	mutt_print_message (tag ? NULL : CURHDR);

#ifdef USE_IMAP
	/* in an IMAP folder index with imap_peek=no, printing could change
	 * new or old messages status to read. Redraw what's needed.
	 */
	if (Context->magic == MUTT_IMAP && !option (OPTIMAPPEEK))
	{
	  menu->redraw |= (tag ? REDRAW_INDEX : REDRAW_CURRENT) | REDRAW_STATUS;
	}
#endif

	break;

      case OP_MAIN_READ_THREAD:
      case OP_MAIN_READ_SUBTHREAD:

	CHECK_MSGCOUNT;
	CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_SEEN, _("Cannot mark message(s) as read"));

	rc = mutt_thread_set_flag (CURHDR, MUTT_READ, 1,
				   op == OP_MAIN_READ_THREAD ? 0 : 1);

	if (rc != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = (op == OP_MAIN_READ_THREAD ?
				  mutt_next_thread (CURHDR) : mutt_next_subthread (CURHDR))) == -1)
	      menu->current = menu->oldcurrent;
	    else if (menu->menu == MENU_PAGER)
	    {
	      op = OP_DISPLAY_MESSAGE;
	      continue;
	    }
	  }
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	}
	break;


      case OP_MARK_MSG:

	CHECK_MSGCOUNT;
	CHECK_VISIBLE;
	if (CURHDR->env->message_id)
	{
	  char str[STRING], macro[STRING];
	  char buf[128];

	  buf[0] = '\0';
          /* L10N: This is the prompt for <mark-message>.  Whatever they
             enter will be prefixed by $mark_macro_prefix and will become
             a macro hotkey to jump to the currently selected message. */
	  if (!mutt_get_field (_("Enter macro stroke: "), buf, sizeof(buf),
	  		       MUTT_CLEAR) && buf[0])
	  {
	    snprintf(str, sizeof(str), "%s%s", MarkMacroPrefix, buf);
	    snprintf(macro, sizeof(macro),
		     "<search>~i \"%s\"\n", CURHDR->env->message_id);
            /* L10N: "message hotkey" is the key bindings menu description of a
               macro created by <mark-message>. */
	    km_bind(str, MENU_MAIN, OP_MACRO, macro, _("message hotkey"));

            /* L10N: This is echoed after <mark-message> creates a new hotkey
               macro.  %s is the hotkey string ($mark_macro_prefix followed
               by whatever they typed at the prompt.) */
	    snprintf(buf, sizeof(buf), _("Message bound to %s."), str);
	    mutt_message(buf);
	    dprint (1, (debugfile, "Mark: %s => %s\n", str, macro));
	  }
	}
	else
          /* L10N: This error is printed if <mark-message> cannot find a
             Message-ID for the currently selected message in the index. */
	  mutt_error _("No message ID to macro.");
	break;

      case OP_RECALL_MESSAGE:

	CHECK_ATTACH;
	ci_send_message (SENDPOSTPONED, NULL, NULL, Context, NULL);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_RESEND:

        CHECK_ATTACH;
        CHECK_MSGCOUNT;
        CHECK_VISIBLE;

        if (tag)
        {
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->tagged)
	      mutt_resend_message (NULL, Context, Context->hdrs[Context->v2r[j]]);
	  }
	}
        else
	  mutt_resend_message (NULL, Context, CURHDR);

        menu->redraw = REDRAW_FULL;
        break;

      case OP_REPLY:

	CHECK_ATTACH;
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (option (OPTPGPAUTODEC) && (tag || !(CURHDR->security & PGP_TRADITIONAL_CHECKED)))
	  mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
	ci_send_message (SENDREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_SHELL_ESCAPE:

	mutt_shell_escape ();
	break;

      case OP_TAG_THREAD:
      case OP_TAG_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	rc = mutt_thread_set_flag (CURHDR, MUTT_TAG, !CURHDR->tagged,
				   op == OP_TAG_THREAD ? 0 : 1);

	if (rc != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    if (op == OP_TAG_THREAD)
	      menu->current = mutt_next_thread (CURHDR);
	    else
	      menu->current = mutt_next_subthread (CURHDR);

	    if (menu->current == -1)
	      menu->current = menu->oldcurrent;
	  }
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_UNDELETE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot undelete message"));

	if (tag)
	{
	  mutt_tag_set_flag (MUTT_DELETE, 0);
	  mutt_tag_set_flag (MUTT_PURGE, 0);
	  menu->redraw |= REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, MUTT_DELETE, 0);
	  mutt_set_flag (Context, CURHDR, MUTT_PURGE, 0);
	  if (option (OPTRESOLVE) && menu->current < Context->vcount - 1)
	  {
	    menu->current++;
	    menu->redraw |= REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw |= REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_UNDELETE_THREAD:
      case OP_UNDELETE_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
        /* L10N: CHECK_ACL */
	CHECK_ACL(MUTT_ACL_DELETE, _("Cannot undelete message(s)"));

	rc = mutt_thread_set_flag (CURHDR, MUTT_DELETE, 0,
				   op == OP_UNDELETE_THREAD ? 0 : 1);
        if (rc != -1)
          rc = mutt_thread_set_flag (CURHDR, MUTT_PURGE, 0,
                                     op == OP_UNDELETE_THREAD ? 0 : 1);
	if (rc != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    if (op == OP_UNDELETE_THREAD)
	      menu->current = mutt_next_thread (CURHDR);
	    else
	      menu->current = mutt_next_subthread (CURHDR);

	    if (menu->current == -1)
	      menu->current = menu->oldcurrent;
	  }
	  menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_VERSION:
	mutt_version ();
	break;

      case OP_BUFFY_LIST:
	mutt_buffy_list ();
	break;

      case OP_VIEW_ATTACHMENTS:
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_view_attachments (CURHDR);
	if (CURHDR->attach_del)
	  Context->changed = 1;
	menu->redraw = REDRAW_FULL;
	break;

      case OP_END_COND:
	break;

      case OP_WHAT_KEY:
	mutt_what_key();
	break;

#ifdef USE_SIDEBAR
      case OP_SIDEBAR_NEXT:
      case OP_SIDEBAR_NEXT_NEW:
      case OP_SIDEBAR_PAGE_DOWN:
      case OP_SIDEBAR_PAGE_UP:
      case OP_SIDEBAR_PREV:
      case OP_SIDEBAR_PREV_NEW:
        mutt_sb_change_mailbox (op);
        break;

      case OP_SIDEBAR_TOGGLE_VISIBLE:
	toggle_option (OPTSIDEBAR);
        mutt_reflow_windows();
	break;
#endif
      default:
	if (menu->menu == MENU_MAIN)
	  km_error_key (MENU_MAIN);
    }

    if (menu->menu == MENU_PAGER)
    {
      mutt_clear_pager_position ();
      menu->menu = MENU_MAIN;
      menu->redraw = REDRAW_FULL;
    }

    if (done) break;
  }

  mutt_pop_current_menu (menu);
  mutt_menuDestroy (&menu);
  return (close);
}