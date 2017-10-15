    for (uids = key->uids; uids; uids = uids->next)
    {
      if (uids->revoked)
	continue;
      if (aka)
      {
	msglen = mutt_strlen (msg) - 4;
	for (i = 0; i < msglen; i++)
	  state_attach_puts(" ", s);
	state_attach_puts(_("aka: "), s);
      }
      state_attach_puts (uids->uid, s);
