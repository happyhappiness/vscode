      case OP_BROWSER_UNSUBSCRIBE:
	imap_subscribe (state.entry[menu->current].name, 0);
	break;

      case OP_BROWSER_TOGGLE_LSUB:
	if (option (OPTIMAPLSUB))
	{
	  unset_option (OPTIMAPLSUB);
	}
	else
	{
	  set_option (OPTIMAPLSUB);
	}
	mutt_ungetch (0, OP_CHECK_NEW);
	break;

      case OP_CREATE_MAILBOX:
	if (!state.imap_browse)
	  mutt_error (_("Create is only supported for IMAP mailboxes"));
	else
	{
	  imap_mailbox_create (LastDir);
	  /* TODO: find a way to detect if the new folder would appear in
	   *   this window, and insert it without starting over. */
	  destroy_state (&state);
	  init_state (&state, NULL);
	  state.imap_browse = 1;
	  imap_browse (LastDir, &state);
	  menu->data = state.entry;
	  menu->current = 0; 
	  menu->top = 0; 
	  init_menu (&state, menu, title, sizeof (title), buffy);
	  MAYBE_REDRAW (menu->redraw);
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
	  snprintf (msg, sizeof (msg), _("Really delete mailbox \"%s\"?"),
            mx.mbox);
	  if (mutt_yesorno (msg, M_NO) == M_YES)
          {
	    if (!imap_delete_mailbox (Context, mx))
            {
	      /* free the mailbox from the browser */
	      safe_free ((void **) &((state.entry)[nentry].name));
	      safe_free ((void **) &((state.entry)[nentry].desc));
	      /* and move all other entries up */
	      if (nentry+1 < state.entrylen)
		memmove (state.entry + nentry, state.entry + nentry + 1,
                  sizeof (struct folder_file) * (state.entrylen - (nentry+1)));
	      state.entrylen--;
	      mutt_message _("Mailbox deleted.");
