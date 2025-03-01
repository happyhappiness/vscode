int mutt_index_menu (void)
{
  char buf[LONG_STRING], helpstr[SHORT_STRING];
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
  
  menu = mutt_new_menu ();
  menu->menu = MENU_MAIN;
  menu->offset = 1;
  menu->pagelen = LINES - 3;
  menu->make_entry = index_make_entry;
  menu->color = index_color;
  menu->current = ci_first_message ();
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_MAIN, IndexHelp);
  
  if (!attach_msg) 
    mutt_buffy_check(1); /* force the buffy check after we enter the folder */

  FOREVER
  {
    tag = 0; /* clear the tag-prefix */

    menu->max = Context ? Context->vcount : 0;
    oldcount = Context ? Context->msgcount : 0;

    /* check if we need to resort the index because just about
     * any 'op' below could do mutt_enter_command(), either here or
     * from any new menu launched, and change $sort/$sort_aux
     */
    if (option (OPTNEEDRESORT) && Context && Context->msgcount)
      resort_index (menu);

    if (Context && !attach_msg)
    {
      int check;
      /* check for new mail in the mailbox.  If nonzero, then something has
       * changed about the file (either we got new mail or the file was
       * modified underneath us.)
       */

#ifdef USE_IMAP
      imap_allow_reopen (Context);
#endif
    
      index_hint = (Context->vcount && menu->current >= 0 && menu->current < Context->vcount) ? CURHDR->index : 0;

      if ((check = mx_check_mailbox (Context, &index_hint, 0)) < 0)
      {
	if (!Context->path)
	{
	  /* fatal error occurred */
	  safe_free ((void **) &Context);
	  menu->redraw = REDRAW_FULL;
	}

	set_option (OPTSEARCHINVALID);
      }
      else if (check == M_NEW_MAIL || check == M_REOPENED || check == M_FLAGS)
      {
	update_index (menu, Context, check, oldcount, index_hint);
	
	/* notify the user of new mail */
	if (check == M_REOPENED)
	  mutt_error _("Mailbox was externally modified.  Flags may be wrong.");
	else if (check == M_NEW_MAIL)
	{
	  mutt_message _("New mail in this mailbox.");
	  if (option (OPTBEEPNEW))
	    beep ();
	} else if (check == M_FLAGS)
	  mutt_message _("Mailbox was externally modified.");

	/* avoid the message being overwritten by buffy */
	do_buffy_notify = 0;
	
	menu->redraw = REDRAW_FULL;
	menu->max = Context->vcount;
	
	set_option (OPTSEARCHINVALID);
      }
    }

#ifdef USE_IMAP
    imap_disallow_reopen (Context);
#endif

    if (!attach_msg)
    {
     /* check for new mail in the incoming folders */
     oldcount = newcount;
     if ((newcount = mutt_buffy_check (0)) != oldcount)
       menu->redraw |= REDRAW_STATUS;
     if (do_buffy_notify)
     {
       if (mutt_buffy_notify () && option (OPTBEEPNEW))
 	beep ();
     }
     else
       do_buffy_notify = 1;
    }

    if (op != -1)
      mutt_curs_set (0);

    if (menu->redraw & REDRAW_FULL)
    {
      menu_redraw_full (menu);
      mutt_show_error ();
    }

    if (menu->menu == MENU_MAIN)
    {
      if (Context && Context->hdrs && !(menu->current >= Context->vcount))
      {
	menu_check_recenter (menu);

	if (menu->redraw & REDRAW_INDEX)
	{
	  menu_redraw_index (menu);
	  menu->redraw |= REDRAW_STATUS;
	}
	else if (menu->redraw & (REDRAW_MOTION_RESYNCH | REDRAW_MOTION))
	  menu_redraw_motion (menu);
	else if (menu->redraw & REDRAW_CURRENT)
	  menu_redraw_current (menu);
      }

      if (menu->redraw & REDRAW_STATUS) 
      {
	menu_status_line (buf, sizeof (buf), menu, NONULL (Status));
	CLEARLINE (option (OPTSTATUSONTOP) ? 0 : LINES-2);
	SETCOLOR (MT_COLOR_STATUS);
	mutt_paddstr (COLS, buf);
	SETCOLOR (MT_COLOR_NORMAL);
	menu->redraw &= ~REDRAW_STATUS;
      }

      menu->redraw = 0;
      if (menu->current < menu->max)
	menu->oldcurrent = menu->current;
      else
	menu->oldcurrent = -1;

      if (option (OPTARROWCURSOR))
	move (menu->current - menu->top + menu->offset, 2);
      else
	move (menu->current - menu->top + menu->offset, COLS - 1);
      mutt_refresh ();

      op = km_dokey (MENU_MAIN);

      dprint(4, (debugfile, "mutt_index_menu[%d]: Got op %d\n", __LINE__, op));

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
      if (SigWinch)
      {
	mutt_flushinp ();
	mutt_resize_screen ();
	menu->redraw = REDRAW_FULL;
	menu->menu = MENU_MAIN;
	SigWinch = 0;
	menu->top = 0; /* so we scroll the right amount */
	continue;
      }
#endif

      if (op == -1)
	continue; /* either user abort or timeout */
      
      mutt_curs_set (1);
      
      /* special handling for the tag-prefix function */
      if (op == OP_TAG_PREFIX)
      {
	if (!Context)
	{
	  mutt_error _("No mailbox is open.");
	  continue;
	}

	if (!Context->tagged)
	{
	  mutt_error _("No tagged messages.");
	  continue;
	}
	tag = 1;

	/* give visual indication that the next command is a tag- command */
	mvaddstr (LINES - 1, 0, "tag-");
	clrtoeol ();

	/* get the real command */
	if ((op = km_dokey (MENU_MAIN)) == OP_TAG_PREFIX)
	{
	  /* abort tag sequence */
	  CLEARLINE (LINES-1);
	  continue;
	}
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
        if (isdigit (LastKey)) mutt_ungetch (LastKey, 0);
	buf[0] = 0;
	if (mutt_get_field (_("Jump to message: "), buf, sizeof (buf), 0) != 0
	    || !buf[0])
	  break;

	if (! isdigit ((unsigned char) buf[0]))
	{
	  mutt_error _("Argument must be a message number.");
	  break;
	}

	i = atoi (buf);
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
	CHECK_ATTACH;
	mutt_pattern_func (M_DELETE, _("Delete messages matching: "));
	menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
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
        CHECK_MSGCOUNT;
	if (!Context->pattern)
	   mutt_message _("No limit pattern is in effect.");
	else
	{
	   char buf[STRING];
	   /* i18n: ask for a limit to apply */
	   snprintf (buf, sizeof(buf), _("Limit: %s"),Context->pattern);
           mutt_message ("%s", buf);
	}
        break;

      case OP_MAIN_LIMIT:

	CHECK_MSGCOUNT;
	menu->oldcurrent = (Context->vcount && menu->current >= 0 && menu->current < Context->vcount) ?
		CURHDR->index : -1;
	if (mutt_pattern_func (M_LIMIT, _("Limit to messages matching: ")) == 0)
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
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	  if ((Sort & SORT_MASK) == SORT_THREADS)
	    mutt_draw_tree (Context);
	}
	break;	  

      case OP_QUIT:

	close = op;
	if (attach_msg)
	{
	 done = 1;
	 break;
	}

	if (query_quadoption (OPT_QUIT, _("Quit Mutt?")) == M_YES)
	{
	  int check;
	  
	  oldcount = Context ? Context->msgcount : 0;

	  if (!Context || (check = mx_close_mailbox (Context, &index_hint)) == 0)
	    done = 1;
	  else
	  {
	    if (check == M_NEW_MAIL || check == M_REOPENED)
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
	}
	break;

      case OP_TAG:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (tag && !option (OPTAUTOTAG))
	{
	  for (j = 0; j < Context->vcount; j++)
	    mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], M_TAG, 0);
	  menu->redraw = REDRAW_STATUS | REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, M_TAG, !CURHDR->tagged);
	  menu->redraw = REDRAW_STATUS;
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
	mutt_pattern_func (M_TAG, _("Tag messages matching: "));
	menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	break;

      case OP_MAIN_UNDELETE_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	if (mutt_pattern_func (M_UNDELETE, _("Undelete messages matching: ")) == 0)
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	break;

      case OP_MAIN_UNTAG_PATTERN:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	if (mutt_pattern_func (M_UNTAG, _("Untag messages matching: ")) == 0)
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	break;

	/* --------------------------------------------------------------------
	 * The following operations can be performed inside of the pager.
	 */

#ifdef USE_IMAP
      case OP_MAIN_IMAP_FETCH:
      	ImapLastCheck = 0;
        break;
#endif
      
      case OP_MAIN_SYNC_FOLDER:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	{
	  int oldvcount = Context->vcount;
	  int oldcount  = Context->msgcount;
	  int dcount = 0;
	  int check;

	  /* calculate the number of messages _above_ the cursor,
	   * so we can keep the cursor on the current message
	   */ 
	  for (j = 0; j <= menu->current; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->deleted)
	      dcount++;
	  }

	  if ((check = mx_sync_mailbox (Context, &index_hint)) == 0)
	  {
	    if (Context->vcount != oldvcount)
	      menu->current -= dcount;
	    set_option (OPTSEARCHINVALID);
	  }
	  else if (check == M_NEW_MAIL || check == M_REOPENED)
	    update_index (menu, Context, check, oldcount, index_hint);

	  /* 
	   * do a sanity check even if mx_sync_mailbox failed.
	   */

	  if (menu->current < 0 || menu->current >= Context->vcount)
	    menu->current = ci_first_message ();
	}

	/* check for a fatal error, or all messages deleted */
	if (!Context->path)
	  safe_free ((void **) &Context);

	/* if we were in the pager, redisplay the message */
	if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
        else
	  menu->redraw = REDRAW_FULL;
	break;

      case OP_MAIN_CHANGE_FOLDER:
      
	if (attach_msg)
	  op = OP_MAIN_CHANGE_FOLDER_READONLY;

	/* fallback to the readonly case */

      case OP_MAIN_CHANGE_FOLDER_READONLY:

        if ((op == OP_MAIN_CHANGE_FOLDER_READONLY) || option (OPTREADONLY))
          cp = _("Open mailbox in read-only mode");
        else
          cp = _("Open mailbox");

	buf[0] = '\0';
	mutt_buffy (buf, sizeof (buf));

	if (mutt_enter_fname (cp, buf, sizeof (buf), &menu->redraw, 1) == -1)
	  break;
	if (!buf[0])
	{
	  CLEARLINE (LINES-1);
	  break;
	}

	mutt_expand_path (buf, sizeof (buf));
	if (mx_get_magic (buf) <= 0)
	{
	  mutt_error (_("%s is not a mailbox."), buf);
	  break;
	}

        if (Context)
        {
	  int check;

	  mutt_str_replace (&LastFolder, Context->path);
	  oldcount = Context ? Context->msgcount : 0;

	  if ((check = mx_close_mailbox (Context, &index_hint)) != 0)
	  {
	    if (check == M_NEW_MAIL || check == M_REOPENED)
	      update_index (menu, Context, check, oldcount, index_hint);
		
	    set_option (OPTSEARCHINVALID);
	    menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	    break;
	  }
	  safe_free ((void **) &Context);
	}

        mutt_sleep (0);
      
	mutt_folder_hook (buf);

	if ((Context = mx_open_mailbox (buf, 
					(option (OPTREADONLY) || op == OP_MAIN_CHANGE_FOLDER_READONLY) ?
					M_READONLY : 0, NULL)) != NULL)
	{
	  menu->current = ci_first_message ();
	}
	else
	  menu->current = 0;

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
 
	if ((op = mutt_display_message (CURHDR)) == -1)
	{
	  unset_option (OPTNEEDRESORT);
	  break;
	}

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
				  _("Exit Mutt without saving?")) == M_YES))
	{
	  if (Context)
	  {
	    mx_fastclose_mailbox (Context);
	    safe_free ((void **) &Context);
	  }
	  done = 1;
	}
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

      case OP_COPY_MESSAGE:
      case OP_SAVE:
      case OP_DECODE_COPY:
      case OP_DECODE_SAVE:
#ifdef HAVE_PGP
      case OP_DECRYPT_COPY:
      case OP_DECRYPT_SAVE:
#endif
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        if (mutt_save_message (tag ? NULL : CURHDR,
#ifdef HAVE_PGP
			       (op == OP_DECRYPT_SAVE) ||
#endif
			       (op == OP_SAVE) || (op == OP_DECODE_SAVE),
			       (op == OP_DECODE_SAVE) || (op == OP_DECODE_COPY),
#ifdef HAVE_PGP
			       (op == OP_DECRYPT_SAVE) || (op == OP_DECRYPT_COPY) ||
#endif
			       0,
			       &menu->redraw) == 0 &&
	    (op == OP_SAVE || op == OP_DECODE_SAVE
#ifdef HAVE_PGP
	     || op == OP_DECRYPT_SAVE
#endif
	     ))
	{
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

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	i = menu->current;
	menu->current = -1;
	for (j = 0; j != Context->vcount; j++)
	{
#define CURHDRi Context->hdrs[Context->v2r[i]] 
	  if (op == OP_MAIN_NEXT_NEW || op == OP_MAIN_NEXT_UNREAD)
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
	    if ((op == OP_MAIN_NEXT_UNREAD || op == OP_MAIN_PREV_UNREAD) &&
		UNREAD (CURHDRi))
	    {
	      menu->current = i;
	      break;
	    }
	    if ((op == OP_MAIN_NEXT_NEW || op == OP_MAIN_PREV_NEW) &&
		UNREAD (CURHDRi) == 1)
	    {
	      menu->current = i;
	      break;
	    }
	  }
	  else if ((!CURHDRi->deleted && !CURHDRi->read))
	  {
	    if (op == OP_MAIN_NEXT_UNREAD || op == OP_MAIN_PREV_UNREAD || !CURHDRi->old)
	    {
	      menu->current = i;
	      break;
	    }
	  }
	}
#undef CURHDRi
	if (menu->current == -1)
	{
	  menu->current = menu->oldcurrent;
	  mutt_error ("%s%s.", (op == OP_MAIN_NEXT_NEW || op == OP_MAIN_PREV_NEW) ? _("No new messages") : _("No unread messages"),
		      Context->pattern ? _(" in this limited view") : "");
	}
	else if (menu->menu == MENU_PAGER)
	{
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
	else
	  menu->redraw = REDRAW_MOTION;
	break;

      case OP_FLAG_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;

#ifdef USE_POP
	if (Context->magic == M_POP)
	{
	  mutt_flushinp ();
	  mutt_error _("Can't change 'important' flag on POP server.");
	  break;
	}
#endif

        if (tag)
        {
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->tagged)
	      mutt_set_flag (Context, Context->hdrs[Context->v2r[j]],
			     M_FLAG, !Context->hdrs[Context->v2r[j]]->flagged);
	  }

	  menu->redraw |= REDRAW_INDEX;
	}
        else
        {
	  mutt_set_flag (Context, CURHDR, M_FLAG, !CURHDR->flagged);
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw = REDRAW_CURRENT;
	    }
	    else
	      menu->redraw = REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw = REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_TOGGLE_NEW:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	if (tag)
	{
	  for (j = 0; j < Context->vcount; j++)
	  {
	    if (Context->hdrs[Context->v2r[j]]->tagged)
	    {
	      if (Context->hdrs[Context->v2r[j]]->read ||
		  Context->hdrs[Context->v2r[j]]->old)
		mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], M_NEW, 1);
	      else
		mutt_set_flag (Context, Context->hdrs[Context->v2r[j]], M_READ, 1);
	    }
	  }
	  menu->redraw = REDRAW_STATUS | REDRAW_INDEX;
	}
	else
	{
	  if (CURHDR->read || CURHDR->old)
	    mutt_set_flag (Context, CURHDR, M_NEW, 1);
	  else
	    mutt_set_flag (Context, CURHDR, M_READ, 1);

	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw = REDRAW_CURRENT;
	    }
	    else
	      menu->redraw = REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw = REDRAW_CURRENT;
	  menu->redraw |= REDRAW_STATUS;
	}
	break;

      case OP_TOGGLE_WRITE:

	CHECK_MSGCOUNT;
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

      case OP_MAIN_PARENT_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;

	if ((menu->current = mutt_parent_message (Context, CURHDR)) < 0)
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
	if (mutt_change_flag (tag ? NULL : CURHDR, (op == OP_MAIN_SET_FLAG)) == 0)
	{
	  menu->redraw = REDRAW_STATUS;
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
	ci_bounce_message (tag ? NULL : CURHDR, &menu->redraw);
	break;

      case OP_CREATE_ALIAS:

        mutt_create_alias (Context && Context->vcount ? CURHDR->env : NULL, NULL);
	MAYBE_REDRAW (menu->redraw);
        menu->redraw |= REDRAW_CURRENT;
	break;

      case OP_QUERY:
	CHECK_ATTACH;
	mutt_query_menu (NULL, 0);
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_DELETE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	if (tag)
	{
	  mutt_tag_set_flag (M_DELETE, 1);
	  if (option (OPTDELETEUNTAG))
	    mutt_tag_set_flag (M_TAG, 0);
	  menu->redraw = REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, M_DELETE, 1);
	  if (option (OPTDELETEUNTAG))
	    mutt_set_flag (Context, CURHDR, M_TAG, 0);
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	    {
	      menu->current = menu->oldcurrent;
	      menu->redraw = REDRAW_CURRENT;
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
	    menu->redraw = REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_DELETE_THREAD:
      case OP_DELETE_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;

	rc = mutt_thread_set_flag (CURHDR, M_DELETE, 1,
				   op == OP_DELETE_THREAD ? 0 : 1);

	if (rc != -1)
	{
	  if (option (OPTDELETEUNTAG))
	    mutt_thread_set_flag (CURHDR, M_TAG, 0, 
				  op == OP_DELETE_THREAD ? 0 : 1);
	  if (option (OPTRESOLVE))
	    if ((menu->current = ci_next_undeleted (menu->current)) == -1)
	      menu->current = menu->oldcurrent;
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_DISPLAY_ADDRESS:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_display_address (CURHDR->env);
	break;

      case OP_ENTER_COMMAND:

	CurrentMenu = MENU_MAIN;
	mutt_enter_command ();
	mutt_check_rescore (Context);
	if (option (OPTFORCEREDRAWINDEX))
	  menu->redraw = REDRAW_FULL;
	unset_option (OPTFORCEREDRAWINDEX);
	unset_option (OPTFORCEREDRAWPAGER);
	break;

      case OP_EDIT_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	CHECK_ATTACH;

#ifdef USE_POP
	if (Context->magic == M_POP)
	{
	  mutt_flushinp ();
	  mutt_error _("Can't edit message on POP server.");
	  break;
	}
#endif

        mutt_edit_message (Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;

	break;

      case OP_FORWARD_MESSAGE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_ATTACH;
	ci_send_message (SENDFORWARD, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;



#ifdef HAVE_PGP
      case OP_FORGET_PASSPHRASE:

	mutt_forget_passphrase ();
	break;
#endif /* HAVE_PGP */



      case OP_GROUP_REPLY:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_ATTACH;
	ci_send_message (SENDREPLY|SENDGROUPREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_LIST_REPLY:

	CHECK_ATTACH;
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	ci_send_message (SENDREPLY|SENDLISTREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_MAIL:

	CHECK_ATTACH;
	ci_send_message (0, NULL, NULL, Context, NULL);
	menu->redraw = REDRAW_FULL;
	break;







#ifdef HAVE_PGP
      case OP_MAIL_KEY:
	
	CHECK_ATTACH;
	ci_send_message (SENDKEY, NULL, NULL, NULL, NULL);
	menu->redraw = REDRAW_FULL;
	break;
      
      case OP_EXTRACT_KEYS:
      
        CHECK_MSGCOUNT;
        CHECK_VISIBLE;
        pgp_extract_keys_from_messages(tag ? NULL : CURHDR);
        menu->redraw = REDRAW_FULL;
        break;

      case OP_CHECK_TRADITIONAL:
      
        CHECK_MSGCOUNT; 
        CHECK_VISIBLE;
        mutt_check_traditional_pgp (tag ? NULL : CURHDR, &menu->redraw);
        if (menu->menu == MENU_PAGER)
        {
	  op = OP_DISPLAY_MESSAGE;
	  continue;
	}
        break;
      
#endif /* HAVE_PGP */







      case OP_PIPE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_pipe_message (tag ? NULL : CURHDR);
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_PRINT:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_print_message (tag ? NULL : CURHDR);
	break;

      case OP_MAIN_READ_THREAD:
      case OP_MAIN_READ_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;

	rc = mutt_thread_set_flag (CURHDR, M_READ, 1,
				   op == OP_MAIN_READ_THREAD ? 0 : 1);

	if (rc != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    if ((menu->oldcurrent = ci_next_undeleted (menu->current)) == -1)
	      menu->oldcurrent = menu->current;
	  }
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	}
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
	ci_send_message (SENDREPLY, NULL, NULL, Context, tag ? NULL : CURHDR);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_SHELL_ESCAPE:

	mutt_shell_escape ();
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_TAG_THREAD:
      case OP_TAG_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	rc = mutt_thread_set_flag (CURHDR, M_TAG, !CURHDR->tagged,
				   op == OP_TAG_THREAD ? 0 : 1);
	
	if (rc != -1)
	{
	  if (option (OPTRESOLVE))
	  {
	    menu->current = mutt_next_thread (CURHDR);

	    if (menu->current == -1)
	      menu->current = menu->oldcurrent;
	  }
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_UNDELETE:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;
	if (tag)
	{
	  mutt_tag_set_flag (M_DELETE, 0);
	  menu->redraw = REDRAW_INDEX;
	}
	else
	{
	  mutt_set_flag (Context, CURHDR, M_DELETE, 0);
	  if (option (OPTRESOLVE) && menu->current < Context->vcount - 1)
	  {
	    menu->current++;
	    menu->redraw = REDRAW_MOTION_RESYNCH;
	  }
	  else
	    menu->redraw = REDRAW_CURRENT;
	}
	menu->redraw |= REDRAW_STATUS;
	break;

      case OP_UNDELETE_THREAD:
      case OP_UNDELETE_SUBTHREAD:

	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	CHECK_READONLY;

	rc = mutt_thread_set_flag (CURHDR, M_DELETE, 0,
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
	  menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	}
	break;

      case OP_VERSION:
	mutt_version ();
	break;

      case OP_VIEW_ATTACHMENTS:
	CHECK_MSGCOUNT;
        CHECK_VISIBLE;
	mutt_view_attachments (CURHDR);
	if (CURHDR->attach_del)
	  Context->changed = 1;
	menu->redraw = REDRAW_FULL;
	break;

      default:
	if (menu->menu == MENU_MAIN)
	  km_error_key (MENU_MAIN);
    }

    if (menu->menu == MENU_PAGER)
    {
      menu->menu = MENU_MAIN;
      menu->redraw = REDRAW_FULL;
#if 0
      set_option (OPTWEED); /* turn header weeding back on. */
#endif
    }

    if (done) break;
  }

#ifdef USE_IMAP
  /* Close all open IMAP connections */
  if (!attach_msg)
    imap_logout_all ();
#endif

  mutt_menuDestroy (&menu);
  return (close);
}