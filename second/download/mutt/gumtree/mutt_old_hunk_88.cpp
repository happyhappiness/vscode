  {
    char buf[LONG_STRING];

    q = p;
    k_info = NULL;

    if ((keyID = mutt_pgp_hook (p)) != NULL)
    {
      int r;
      snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
      if ((r = mutt_yesorno (buf, M_YES)) == M_YES)
      {
	/* check for e-mail address */
	if ((t = strchr (keyID, '@')) && 
	    (addr = rfc822_parse_adrlist (NULL, keyID)))
	{
	  if (fqdn) rfc822_qualify (addr, fqdn);
	  q = addr;
	}
	else
	  k_info = pgp_getkeybystr (keyID, KEYFLAG_CANENCRYPT, PGP_PUBRING);
      }
      else if (r == -1)
      {
	safe_free ((void **) &keylist);
	rfc822_free_address (&tmp);
	rfc822_free_address (&addr);
	return NULL;
      }
    }

