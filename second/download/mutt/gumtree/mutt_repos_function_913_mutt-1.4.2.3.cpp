int mutt_menuLoop (MUTTMENU *menu)
{
  int i = OP_NULL;

  FOREVER
  {
    if (option (OPTMENUCALLER))
    {
      unset_option (OPTMENUCALLER);
      return OP_NULL;
    }
    
    
    mutt_curs_set (0);

#ifdef USE_IMAP
    imap_keepalive ();
#endif

    /* See if all or part of the screen needs to be updated.  */
    if (menu->redraw & REDRAW_FULL)
    {
      menu_redraw_full (menu);
      /* allow the caller to do any local configuration */
      return (OP_REDRAW);
    }

    if (!menu->dialog)
      menu_check_recenter (menu);

    if (menu->redraw & REDRAW_STATUS)
      menu_redraw_status (menu);
    if (menu->redraw & REDRAW_INDEX)
      menu_redraw_index (menu);
    else if (menu->redraw & (REDRAW_MOTION | REDRAW_MOTION_RESYNCH))
      menu_redraw_motion (menu);
    else if (menu->redraw == REDRAW_CURRENT)
      menu_redraw_current (menu);

    if (menu->dialog)
      menu_redraw_prompt (menu);
    
    menu->oldcurrent = menu->current;


    /* move the cursor out of the way */
    move (menu->current - menu->top + menu->offset,
	  (option (OPTARROWCURSOR) ? 2 : COLS-1));

    mutt_refresh ();
    
    /* try to catch dialog keys before ops */
    if (menu->dialog && menu_dialog_dokey (menu, &i) == 0)
      return i;
		    
    i = km_dokey (menu->menu);
    if (i == OP_TAG_PREFIX)
    {
      if (menu->tagged)
      {
	mvaddstr (LINES - 1, 0, "Tag-");
	clrtoeol ();
	i = km_dokey (menu->menu);
	menu->tagprefix = 1;
	CLEARLINE (LINES - 1);
      }
      else 
      {
	mutt_error _("No tagged entries.");
	i = -1;
      }
    }
    else if (menu->tagged && option (OPTAUTOTAG))
      menu->tagprefix = 1;
    else
      menu->tagprefix = 0;

    mutt_curs_set (1);

#if defined (USE_SLANG_CURSES) || defined (HAVE_RESIZETERM)
    if (SigWinch)
    {
      mutt_resize_screen ();
      menu->redraw = REDRAW_FULL;
      SigWinch = 0;
    }
#endif

    if (i == -1)
      continue;

    if (!menu->dialog)
      mutt_clear_error ();

    /* Convert menubar movement to scrolling */
    if (menu->dialog) 
      i = menu_dialog_translate_op (i);

    switch (i)
    {
      case OP_NEXT_ENTRY:
	menu_next_entry (menu);
	break;
      case OP_PREV_ENTRY:
	menu_prev_entry (menu);
	break;
      case OP_HALF_DOWN:
	menu_half_down (menu);
	break;
      case OP_HALF_UP:
	menu_half_up (menu);
	break;
      case OP_NEXT_PAGE:
	menu_next_page (menu);
	break;
      case OP_PREV_PAGE:
	menu_prev_page (menu);
	break;
      case OP_NEXT_LINE:
	menu_next_line (menu);
	break;
      case OP_PREV_LINE:
	menu_prev_line (menu);
	break;
      case OP_FIRST_ENTRY:
	menu_first_entry (menu);
	break;
      case OP_LAST_ENTRY:
	menu_last_entry (menu);
	break;
      case OP_TOP_PAGE:
	menu_top_page (menu);
	break;
      case OP_MIDDLE_PAGE:
	menu_middle_page (menu);
	break;
      case OP_BOTTOM_PAGE:
	menu_bottom_page (menu);
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
      case OP_SEARCH:
      case OP_SEARCH_REVERSE:
      case OP_SEARCH_NEXT:
      case OP_SEARCH_OPPOSITE:
	if (menu->search && !menu->dialog) /* Searching dialogs won't work */
	{
	  menu->oldcurrent = menu->current;
	  if ((menu->current = menu_search (menu, i)) != -1)
	    menu->redraw = REDRAW_MOTION;
	  else
	    menu->current = menu->oldcurrent;
	}
	else
	  mutt_error _("Search is not implemented for this menu.");
	break;

      case OP_JUMP:
	if (menu->dialog)
	  mutt_error _("Jumping is not implemented for dialogs.");
	else
	  menu_jump (menu);
	break;

      case OP_ENTER_COMMAND:
	CurrentMenu = menu->menu;
	mutt_enter_command ();
	if (option (OPTFORCEREDRAWINDEX))
	{
	  menu->redraw = REDRAW_FULL;
	  unset_option (OPTFORCEREDRAWINDEX);
	  unset_option (OPTFORCEREDRAWPAGER);
	}
	break;

      case OP_TAG:
	if (menu->tag && !menu->dialog)
	{
	  if (menu->tagprefix && !option (OPTAUTOTAG))
	  {
	    for (i = 0; i < menu->max; i++)
	      menu->tagged += menu->tag (menu, i, 0);
	    menu->redraw = REDRAW_INDEX;
	  }
	  else if (menu->max)
	  {
	    int i = menu->tag (menu, menu->current, -1);
	    menu->tagged += i;
	    if (i && option (OPTRESOLVE) && menu->current < menu->max - 1)
	    {
	      menu->current++;
	      menu->redraw = REDRAW_MOTION_RESYNCH;
	    }
	    else
	      menu->redraw = REDRAW_CURRENT;
	  }
	  else
	    mutt_error _("No entries.");
	}
	else
	  mutt_error _("Tagging is not supported.");
	break;

      case OP_SHELL_ESCAPE:
	mutt_shell_escape ();
	MAYBE_REDRAW (menu->redraw);
	break;

      case OP_REDRAW:
	clearok (stdscr, TRUE);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_HELP:
	mutt_help (menu->menu);
	menu->redraw = REDRAW_FULL;
	break;

      case OP_NULL:
	km_error_key (menu->menu);
	break;

      default:
	return (i);
    }
  }
  /* not reached */
}