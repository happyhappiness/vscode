static void init_menu (struct browser_state *state, MUTTMENU *menu, char *title,
		       size_t titlelen, int buffy)
{
  char path[_POSIX_PATH_MAX];

  menu->max = state->entrylen;

  if(menu->current >= menu->max)
    menu->current = menu->max - 1;
  if (menu->current < 0)
    menu->current = 0;
  if (menu->top > menu->current)
    menu->top = 0;

  menu->tagged = 0;
  
  if (buffy)
    snprintf (title, titlelen, _("Mailboxes [%d]"), mutt_buffy_check (0));
  else
  {
    strfcpy (path, LastDir, sizeof (path));
    mutt_pretty_mailbox (path, sizeof (path));
#ifdef USE_IMAP
  if (state->imap_browse && option (OPTIMAPLSUB))
    snprintf (title, titlelen, _("Subscribed [%s], File mask: %s"),
	      path, NONULL (Mask.pattern));
  else
#endif
    snprintf (title, titlelen, _("Directory [%s], File mask: %s"),
	      path, NONULL(Mask.pattern));
  }
  menu->redraw = REDRAW_FULL;
}