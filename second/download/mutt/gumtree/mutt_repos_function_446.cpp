int mutt_buffy_list (void)
{
  BUFFY *tmp;
  char path[_POSIX_PATH_MAX];
  char buffylist[2*STRING];
  size_t pos = 0;
  int first = 1;

  int have_unnotified = BuffyNotify;
  
  buffylist[0] = 0;
  pos += strlen (strncat (buffylist, _("New mail in "), sizeof (buffylist) - 1 - pos)); /* __STRNCAT_CHECKED__ */
  for (tmp = Incoming; tmp; tmp = tmp->next)
  {
    /* Is there new mail in this mailbox? */
    if (!tmp->new || (have_unnotified && tmp->notified))
      continue;

    strfcpy (path, tmp->path, sizeof (path));
    mutt_pretty_mailbox (path, sizeof (path));
    
    if (!first && (MuttMessageWindow->cols >= 7) &&
        (pos + strlen (path) >= (size_t)MuttMessageWindow->cols - 7))
      break;
    
    if (!first)
      pos += strlen (strncat(buffylist + pos, ", ", sizeof(buffylist)-1-pos)); /* __STRNCAT_CHECKED__ */

    /* Prepend an asterisk to mailboxes not already notified */
    if (!tmp->notified)
    {
      /* pos += strlen (strncat(buffylist + pos, "*", sizeof(buffylist)-1-pos));  __STRNCAT_CHECKED__ */
      tmp->notified = 1;
      BuffyNotify--;
    }
    pos += strlen (strncat(buffylist + pos, path, sizeof(buffylist)-1-pos)); /* __STRNCAT_CHECKED__ */
    first = 0;
  }
  if (!first && tmp)
  {
    strncat (buffylist + pos, ", ...", sizeof (buffylist) - 1 - pos); /* __STRNCAT_CHECKED__ */
  }
  if (!first)
  {
    mutt_message ("%s", buffylist);
    return (1);
  }
  /* there were no mailboxes needing to be notified, so clean up since 
   * BuffyNotify has somehow gotten out of sync
   */
  BuffyNotify = 0;
  return (0);
}