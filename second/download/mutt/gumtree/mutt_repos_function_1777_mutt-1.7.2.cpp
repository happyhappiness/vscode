pgp_key_t pgp_getkeybyaddr (ADDRESS * a, short abilities, pgp_ring_t keyring,
                            int oppenc_mode)
{
  ADDRESS *r, *p;
  LIST *hints = NULL;

  int multi   = 0;
  int match;

  pgp_key_t keys, k, kn;
  pgp_key_t the_strong_valid_key = NULL;
  pgp_key_t a_valid_addrmatch_key = NULL;
  pgp_key_t matches = NULL;
  pgp_key_t *last = &matches;
  pgp_uid_t *q;

  if (a && a->mailbox)
    hints = pgp_add_string_to_hints (hints, a->mailbox);
  if (a && a->personal)
    hints = pgp_add_string_to_hints (hints, a->personal);

  if (! oppenc_mode )
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

    match                = 0;   /* any match 		  */

    for (q = k->address; q; q = q->next)
    {
      r = rfc822_parse_adrlist (NULL, NONULL (q->addr));

      for (p = r; p; p = p->next)
      {
	int validity = pgp_id_matches_addr (a, p, q);

	if (validity & PGP_KV_MATCH)	/* something matches */
	  match = 1;

        if ((validity & PGP_KV_VALID)
            && (validity & PGP_KV_ADDR))
        {
          if (validity & PGP_KV_STRONGID)
          {
            if (the_strong_valid_key && the_strong_valid_key != k)
              multi = 1;
            the_strong_valid_key = k;
          }
          else
          {
            a_valid_addrmatch_key = k;
          }
        }
      }

      rfc822_free_address (&r);
    }

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
    if (oppenc_mode)
    {
      if (the_strong_valid_key)
      {
        pgp_remove_key (&matches, the_strong_valid_key);
        k = the_strong_valid_key;
      }
      else if (a_valid_addrmatch_key)
      {
        pgp_remove_key (&matches, a_valid_addrmatch_key);
        k = a_valid_addrmatch_key;
      }
      else
        k = NULL;
    }
    else if (the_strong_valid_key && !multi)
    {
      /*
       * There was precisely one strong match on a valid ID.
       * 
       * Proceed without asking the user.
       */
      pgp_remove_key (&matches, the_strong_valid_key);
      k = the_strong_valid_key;
    }
    else 
    {
      /* 
       * Else: Ask the user.
       */
      if ((k = pgp_select_key (matches, a, NULL)))
	pgp_remove_key (&matches, k);
    }

    pgp_free_key (&matches);

    return k;
  }

  return NULL;
}