pgp_key_t pgp_getkeybystr (char *p, short abilities, pgp_ring_t keyring)
{
  LIST *hints = NULL;
  pgp_key_t keys;
  pgp_key_t matches = NULL;
  pgp_key_t *last = &matches;
  pgp_key_t k, kn;
  pgp_uid_t *a;
  short match;
  size_t l;
  const char *ps, *pl, *pfcopy, *phint;

  if ((l = mutt_strlen (p)) && p[l-1] == '!')
    p[l-1] = 0;

  mutt_message (_("Looking for keys matching \"%s\"..."), p);

  pfcopy = crypt_get_fingerprint_or_id (p, &phint, &pl, &ps);
  hints = pgp_add_string_to_hints (hints, phint);
  keys = pgp_get_candidates (keyring, hints);
  mutt_free_list (&hints);

  if (!keys)
    goto out;

  for (k = keys; k; k = kn)
  {
    kn = k->next;
    if (abilities && !(k->flags & abilities))
      continue;

    /* This shouldn't happen, but keys without any addresses aren't selectable
     * in pgp_select_key().
     */
    if (!k->address)
      continue;

    match = 0;

    dprint (5, (debugfile, "pgp_getkeybystr: matching \"%s\" against key %s:\n",
                p, pgp_long_keyid (k)));

    if (!*p ||
        (pfcopy && mutt_strcasecmp (pfcopy, k->fingerprint) == 0) ||
        (pl && mutt_strcasecmp (pl, pgp_long_keyid (k)) == 0) ||
        (ps && mutt_strcasecmp (ps, pgp_short_keyid (k)) == 0))
    {
      dprint (5, (debugfile, "\t\tmatch.\n"));
      match = 1;
    }
    else
    {
      for (a = k->address; a; a = a->next)
      {
        dprint (5, (debugfile, "pgp_getkeybystr: matching \"%s\" against key %s, \"%s\":\n",
                    p, pgp_long_keyid (k), NONULL (a->addr)));
        if (mutt_stristr (a->addr, p))
        {
          dprint (5, (debugfile, "\t\tmatch.\n"));
          match = 1;
          break;
        }
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
    FREE (&pfcopy);
    if (l && !p[l-1])
      p[l-1] = '!';
    return k;
  }

out:
  FREE (&pfcopy);
  if (l && !p[l-1])
    p[l-1] = '!';
  return NULL;
}