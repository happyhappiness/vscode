  t->subtype = safe_strdup ("pgp-signature");
  t->filename = safe_strdup (sigfile);
  t->use_disp = 0;
  t->disposition = DISPNONE;
  t->encoding = ENC7BIT;
  t->unlink = 1; /* ok to remove this file after sending. */

  return (a);
}

static short is_numerical_keyid (const char *s)
{
  /* or should we require the "0x"? */
  if (strncmp (s, "0x", 2) == 0)
    s += 2;
  if (strlen (s) % 8)
    return 0;
  while (*s)
    if (strchr ("0123456789ABCDEFabcdef", *s++) == NULL)
      return 0;
  
  return 1;
}

/* This routine attempts to find the keyids of the recipients of a message.
 * It returns NULL if any of the keys can not be found.
 */
char *pgp_findKeys (ADDRESS *to, ADDRESS *cc, ADDRESS *bcc)
{
  char *keyID, *keylist = NULL;
  size_t keylist_size = 0;
  size_t keylist_used = 0;
  ADDRESS *tmp = NULL, *addr = NULL;
  ADDRESS **last = &tmp;
  ADDRESS *p, *q;
  int i;
  pgp_key_t k_info = NULL, key = NULL;

  const char *fqdn = mutt_fqdn (1);

  for (i = 0; i < 3; i++) 
  {
    switch (i)
    {
      case 0: p = to; break;
      case 1: p = cc; break;
      case 2: p = bcc; break;
      default: abort ();
    }
    
    *last = rfc822_cpy_adr (p, 0);
    while (*last)
      last = &((*last)->next);
  }

  if (fqdn)
    rfc822_qualify (tmp, fqdn);

  tmp = mutt_remove_duplicates (tmp);
  
  for (p = tmp; p ; p = p->next)
  {
    char buf[LONG_STRING];

    q = p;
    k_info = NULL;

    if ((keyID = mutt_crypt_hook (p)) != NULL)
    {
      int r;
      snprintf (buf, sizeof (buf), _("Use keyID = \"%s\" for %s?"), keyID, p->mailbox);
      if ((r = mutt_yesorno (buf, M_YES)) == M_YES)
      {
	if (is_numerical_keyid (keyID))
	{
	  if (strncmp (keyID, "0x", 2) == 0)
	    keyID += 2;
	  goto bypass_selection;		/* you don't see this. */
	}
	
	/* check for e-mail address */
	if (strchr (keyID, '@') && 
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
	FREE (&keylist);
	rfc822_free_address (&tmp);
	rfc822_free_address (&addr);
	return NULL;
      }
    }

    if (k_info == NULL)
      pgp_invoke_getkeys (q);

    if (k_info == NULL && (k_info = pgp_getkeybyaddr (q, KEYFLAG_CANENCRYPT, PGP_PUBRING)) == NULL)
    {
      snprintf (buf, sizeof (buf), _("Enter keyID for %s: "), q->mailbox);

      if ((key = pgp_ask_for_key (buf, q->mailbox,
				  KEYFLAG_CANENCRYPT, PGP_PUBRING)) == NULL)
      {
	FREE (&keylist);
	rfc822_free_address (&tmp);
	rfc822_free_address (&addr);
	return NULL;
      }
    }
    else
      key = k_info;

    keyID = pgp_keyid (key);
    
  bypass_selection:
    keylist_size += mutt_strlen (keyID) + 4;
    safe_realloc (&keylist, keylist_size);
    sprintf (keylist + keylist_used, "%s0x%s", keylist_used ? " " : "",	/* __SPRINTF_CHECKED__ */
	     keyID);
    keylist_used = mutt_strlen (keylist);

    pgp_free_key (&key);
    rfc822_free_address (&addr);

  }
  rfc822_free_address (&tmp);
  return (keylist);
}

/* Warning: "a" is no longer freed in this routine, you need
 * to free it later.  This is necessary for $fcc_attach. */

