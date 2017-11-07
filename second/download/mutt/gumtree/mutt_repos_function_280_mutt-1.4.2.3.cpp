void mutt_buffy (char *s, size_t slen)
{
  int count;
  BUFFY *tmp = Incoming;

  mutt_expand_path (s, _POSIX_PATH_MAX);
  switch (mutt_buffy_check (0))
  {
  case 0:

    s = '\0';
    break;

  case 1:

    while (tmp && !tmp->new)
      tmp = tmp->next;
    if (!tmp)
    {
      s = '\0';
      mutt_buffy_check (1); /* buffy was wrong - resync things */
      break;
    }
    strfcpy (s, tmp->path, slen);
    mutt_pretty_mailbox (s);
    break;

  default:
    
    count = 0;
    while (count < 3)
    {
      if (mutt_strcmp (s, tmp->path) == 0)
	count++;
      else if (count && tmp->new)
	break;
      tmp = tmp->next;
      if (!tmp)
      {
	tmp = Incoming;
	count++;
      }
    }
    if (count >= 3)
    {
      s = '\0';
      mutt_buffy_check (1); /* buffy was wrong - resync things */
      break;
    }
    strfcpy (s, tmp->path, slen);
    mutt_pretty_mailbox (s);
    break;
  }
}