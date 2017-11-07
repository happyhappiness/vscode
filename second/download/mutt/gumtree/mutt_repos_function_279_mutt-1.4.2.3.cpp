int mutt_buffy_notify (void)
{
  BUFFY *tmp;
  char path[_POSIX_PATH_MAX];

  if (mutt_buffy_check (0) && BuffyNotify)
  {
    for (tmp = Incoming; tmp; tmp = tmp->next)
    {
      if (tmp->new && !tmp->notified)
      {
	strfcpy (path, tmp->path, sizeof (path));
	mutt_pretty_mailbox (path);
	mutt_message (_("New mail in %s."), path);
	tmp->notified = 1;
	BuffyNotify--;
	return (1);
      }
    }
    /* there were no mailboxes needing to be notified, so clean up since 
     * BuffyNotify has somehow gottten out of sync
     */
    BuffyNotify = 0;
  }
  return (0);
}