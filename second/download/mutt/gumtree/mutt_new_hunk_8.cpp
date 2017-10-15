      case OP_BROWSER_UNSUBSCRIBE:
	imap_subscribe (state.entry[menu->current].name, 0);
	break;

      case OP_BROWSER_TOGGLE_LSUB:
	if (option (OPTIMAPLSUB))
	  unset_option (OPTIMAPLSUB);
	else
	  set_option (OPTIMAPLSUB);

	mutt_ungetch (0, OP_CHECK_NEW);
	break;

      case OP_CREATE_MAILBOX:
	if (!state.imap_browse)
	{
	  mutt_error (_("Create is only supported for IMAP mailboxes"));
	  break;
	}

	if (!imap_mailbox_create (LastDir))
	{
	  /* TODO: find a way to detect if the new folder would appear in
	   *   this window, and insert it without starting over. */
	  destroy_state (&state);
	  init_state (&state, NULL);
	  state.imap_browse = 1;
	  imap_browse (LastDir, &state);
	  browser_sort (&state);
	  menu->data = state.entry;
	  menu->current = 0; 
	  menu->top = 0; 
	  init_menu (&state, menu, title, sizeof (title), buffy);
	  MAYBE_REDRAW (menu->redraw);
	}
	/* else leave error on screen */
	break;

      case OP_RENAME_MAILBOX:
	if (!state.entry[menu->current].imap)
	  mutt_error (_("Rename is only supported for IMAP mailboxes"));
	else
	{
	  int nentry = menu->current;

	  if (imap_mailbox_rename (state.entry[nentry].name) >= 0)
	  {
	    destroy_state (&state);
	    init_state (&state, NULL);
	    state.imap_browse = 1;
	    imap_browse (LastDir, &state);
	    browser_sort (&state);
	    menu->data = state.entry;
	    menu->current = 0;
	    menu->top = 0;
	    init_menu (&state, menu, title, sizeof (title), buffy);
	    MAYBE_REDRAW (menu->redraw);
	  }
	}
	break;

    case OP_DELETE_MAILBOX:
	if (!state.entry[menu->current].imap)
	  mutt_error (_("Delete is only supported for IMAP mailboxes"));
	else
        {
	  char msg[SHORT_STRING];
	  IMAP_MBOX mx;
	  int nentry = menu->current;

	  imap_parse_path (state.entry[nentry].name, &mx);
	  if (!mx.mbox)
	  {
	    mutt_error _("Cannot delete root folder");
	    break;
	  }
	  snprintf (msg, sizeof (msg), _("Really delete mailbox \"%s\"?"),
            mx.mbox);
	  if (mutt_yesorno (msg, M_NO) == M_YES)
          {
	    if (!imap_delete_mailbox (Context, mx))
            {
	      /* free the mailbox from the browser */
	      FREE (&((state.entry)[nentry].name));
	      FREE (&((state.entry)[nentry].desc));
	      /* and move all other entries up */
	      if (nentry+1 < state.entrylen)
		memmove (state.entry + nentry, state.entry + nentry + 1,
                  sizeof (struct folder_file) * (state.entrylen - (nentry+1)));
	      state.entrylen--;
	      mutt_message _("Mailbox deleted.");
