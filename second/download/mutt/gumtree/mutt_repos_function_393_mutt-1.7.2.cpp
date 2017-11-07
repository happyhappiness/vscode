static HEADER *select_msg (void)
{
  MUTTMENU *menu;
  int i, done=0, r=-1;
  char helpstr[LONG_STRING];
  short orig_sort;

  menu = mutt_new_menu (MENU_POST);
  menu->make_entry = post_entry;
  menu->max = PostContext->msgcount;
  menu->title = _("Postponed Messages");
  menu->data = PostContext;
  menu->help = mutt_compile_help (helpstr, sizeof (helpstr), MENU_POST, PostponeHelp);

  /* The postponed mailbox is setup to have sorting disabled, but the global
   * Sort variable may indicate something different.   Sorting has to be
   * disabled while the postpone menu is being displayed. */
  orig_sort = Sort;
  Sort = SORT_ORDER;

  while (!done)
  {
    switch (i = mutt_menuLoop (menu))
    {
      case OP_DELETE:
      case OP_UNDELETE:
        /* should deleted draft messages be saved in the trash folder? */
	mutt_set_flag (PostContext, PostContext->hdrs[menu->current], MUTT_DELETE, (i == OP_DELETE) ? 1 : 0);
	PostCount = PostContext->msgcount - PostContext->deleted;
	if (option (OPTRESOLVE) && menu->current < menu->max - 1)
	{
	  menu->oldcurrent = menu->current;
	  menu->current++;
	  if (menu->current >= menu->top + menu->pagelen)
	  {
	    menu->top = menu->current;
	    menu->redraw = REDRAW_INDEX | REDRAW_STATUS;
	  }
	  else
	    menu->redraw |= REDRAW_MOTION_RESYNCH;
	}
	else
	  menu->redraw = REDRAW_CURRENT;
	break;

      case OP_GENERIC_SELECT_ENTRY:
	r = menu->current;
	done = 1;
	break;

      case OP_EXIT:
	done = 1;
	break;
    }
  }

  Sort = orig_sort;
  mutt_menuDestroy (&menu);
  return (r > -1 ? PostContext->hdrs[r] : NULL);
}