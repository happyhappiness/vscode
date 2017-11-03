void mutt_buffy (char *s, size_t slen)
{
  BUFFY *tmp = Incoming;
  int pass, found = 0;

  mutt_expand_path (s, slen);

  if (mutt_buffy_check (0)) 
  {
    for (pass = 0; pass < 2; pass++)
      for (tmp = Incoming; tmp; tmp = tmp->next) 
      {
	mutt_expand_path (tmp->path, sizeof (tmp->path));
	if ((found || pass) && tmp->new) 
	{
	  strfcpy (s, tmp->path, slen);
	  mutt_pretty_mailbox (s, slen);
	  return;
	}
	if (mutt_strcmp (s, tmp->path) == 0)
	  found = 1;
      }

    mutt_buffy_check (1); /* buffy was wrong - resync things */
  }

  /* no folders with new mail */
  *s = '\0';
}