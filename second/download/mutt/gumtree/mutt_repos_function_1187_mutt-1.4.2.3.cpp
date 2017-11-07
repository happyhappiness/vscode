pgp_key_t *pgp_getkeybystr (char *p, short abilities, pgp_ring_t keyring)
{
  LIST *hints = NULL;
  pgp_key_t *keys;
  pgp_key_t *matches = NULL;
  pgp_key_t **last = &matches;
  pgp_key_t *k, *kn;
  pgp_uid_t *a;
  short match;

  mutt_message (_("Looking for keys matching \"%s\"..."), p);
  
  hints = pgp_add_string_to_hints (hints, p);
  keys = pgp_get_candidates (keyring, hints);
  mutt_free_list (&hints);

  if (!keys)
    return NULL;
  
  
  for (k = keys; k; k = kn)
  {
    kn = k->next;
    if (abilities && !(k->flags & abilities))
      continue;

    match = 0;
    
    for (a = k->address; a; a = a->next)
    {
      dprint (5, (debugfile, "pgp_getkeybystr: matching \"%s\" against key %s, \"%s\": ",
		  p, pgp_keyid (k), a->addr));
      if (!*p || mutt_strcasecmp (p, pgp_keyid (k)) == 0 ||
	  (!mutt_strncasecmp (p, "0x", 2) && !mutt_strcasecmp (p + 2, pgp_keyid (k))) ||
	  (option (OPTPGPLONGIDS) && !mutt_strncasecmp (p, "0x", 2) &&
	   !mutt_strcasecmp (p + 2, k->keyid + 8)) ||
	  mutt_stristr (a->addr, p))
      {
	dprint (5, (debugfile, "match.\n"));
	match = 1;
	break;
      }
    }
    
    if (match)
    {
      *last = pgp_principal_key (k);
      kn    = pgp_remove_key (&keys, *last);
      last  = pgp_get_lastp (k);
    }
  }

  pgp_free_key (&keys);

  if (matches)
  {
    if ((k = pgp_select_key (matches, NULL, p)))
      pgp_remove_key (&matches, k);
    
    pgp_free_key (&matches);
    return k;
  }

  return NULL;
}