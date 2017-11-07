pgp_key_t *pgp_getkeybyaddr (ADDRESS * a, short abilities, pgp_ring_t keyring)
{
  ADDRESS *r, *p;
  LIST *hints = NULL;

  int weak    = 0;
  int invalid = 0;
  int multi   = 0;
  int this_key_has_strong;
  int this_key_has_weak;
  int this_key_has_invalid;
  int match;

  pgp_key_t *keys, *k, *kn;
  pgp_key_t *the_valid_key = NULL;
  pgp_key_t *matches = NULL;
  pgp_key_t **last = &matches;
  pgp_uid_t *q;
  
  if (a && a->mailbox)
    hints = pgp_add_string_to_hints (hints, a->mailbox);
  if (a && a->personal)
    hints = pgp_add_string_to_hints (hints, a->personal);

  mutt_message (_("Looking for keys matching \"%s\"..."), a->mailbox);
  keys = pgp_get_candidates (keyring, hints);

  mutt_free_list (&hints);
  
  if (!keys)
    return NULL;
  
  dprint (5, (debugfile, "pgp_getkeybyaddr: looking for %s <%s>.",
	      a->personal, a->mailbox));


  for (k = keys; k; k = kn)
  {
    kn = k->next;

    dprint (5, (debugfile, "  looking at key: %s\n",
		pgp_keyid (k)));

    if (abilities && !(k->flags & abilities))
    {
      dprint (5, (debugfile, "  insufficient abilities: Has %x, want %x\n",
		  k->flags, abilities));
      continue;
    }

    this_key_has_weak    = 0;	/* weak but valid match   */
    this_key_has_invalid = 0;   /* invalid match          */
    this_key_has_strong  = 0;	/* strong and valid match */
    match                = 0;   /* any match 		  */

    for (q = k->address; q; q = q->next)
    {
      r = rfc822_parse_adrlist (NULL, q->addr);

      for (p = r; p; p = p->next)
      {
	int validity = pgp_id_matches_addr (a, p, q);

	if (validity & PGP_KV_MATCH)	/* something matches */
	  match = 1;

	/* is this key a strong candidate? */
	if ((validity & PGP_KV_VALID) && (validity & PGP_KV_STRONGID) 
	    && (validity & PGP_KV_ADDR))
	{
	  if (the_valid_key && the_valid_key != k)
	    multi             = 1;
	  the_valid_key       = k;
	  this_key_has_strong = 1;
	}
	else if ((validity & PGP_KV_MATCH) && !(validity & PGP_KV_VALID))
	  this_key_has_invalid = 1;
	else if ((validity & PGP_KV_MATCH) 
		 && (!(validity & PGP_KV_STRONGID) || !(validity & PGP_KV_ADDR)))
	  this_key_has_weak    = 1;
      }

      rfc822_free_address (&r);
    }

    if (match && !this_key_has_strong && this_key_has_invalid)
      invalid = 1;
    if (match && !this_key_has_strong && this_key_has_weak)
      weak = 1;
    
    if (match)
    {
      *last  = pgp_principal_key (k);
      kn     = pgp_remove_key (&keys, *last);
      last   = pgp_get_lastp (k);
    }
  }

  pgp_free_key (&keys);
  
  if (matches)
  {
    if (the_valid_key && !multi && !weak 
	&& !(invalid && option (OPTPGPSHOWUNUSABLE)))
    {	
      /* 
       * There was precisely one strong match on a valid ID, there
       * were no valid keys with weak matches, and we aren't
       * interested in seeing invalid keys.
       * 
       * Proceed without asking the user.
       */
      pgp_remove_key (&matches, the_valid_key);
      pgp_free_key (&matches);
      k = the_valid_key;
    }
    else 
    {
      /* 
       * Else: Ask the user.
       */
      if ((k = pgp_select_key (matches, a, NULL)))
	pgp_remove_key (&matches, k);
      pgp_free_key (&matches);
    }

    return k;
  }

  return NULL;
}