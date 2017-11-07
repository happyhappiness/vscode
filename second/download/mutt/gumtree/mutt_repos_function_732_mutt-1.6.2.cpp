static crypt_key_t *crypt_getkeybystr (char *p, short abilities,
				       unsigned int app, int *forced_valid)
{
  LIST *hints = NULL;
  crypt_key_t *keys;
  crypt_key_t *matches = NULL;
  crypt_key_t **matches_endp = &matches;
  crypt_key_t *k;
  const char *ps, *pl, *pfcopy, *phint;

  mutt_message (_("Looking for keys matching \"%s\"..."), p);

  *forced_valid = 0;

  pfcopy = crypt_get_fingerprint_or_id (p, &phint, &pl, &ps);
  hints = crypt_add_string_to_hints (hints, phint);
  keys = get_candidates (hints, app, (abilities & KEYFLAG_CANSIGN));
  mutt_free_list (&hints);

  if (!keys)
  {
    FREE (&pfcopy);
    return NULL;
  }

  for (k = keys; k; k = k->next)
    {
      if (abilities && !(k->flags & abilities))
        continue;

      dprint (5, (debugfile, "crypt_getkeybystr: matching \"%s\" against "
                  "key %s, \"%s\": ",  p, crypt_long_keyid (k), k->uid));

      if (!*p
          || (pfcopy && mutt_strcasecmp (pfcopy, crypt_fpr (k)) == 0)
          || (pl && mutt_strcasecmp (pl, crypt_long_keyid (k)) == 0)
          || (ps && mutt_strcasecmp (ps, crypt_short_keyid (k)) == 0)
          || mutt_stristr (k->uid, p))
        {
          crypt_key_t *tmp;

          dprint (5, (debugfile, "match.\n"));

          *matches_endp = tmp = crypt_copy_key (k);
          matches_endp = &tmp->next;
        }
    }
  
  FREE (&pfcopy);
  crypt_free_key (&keys);
  
  if (matches)
    {
      k = crypt_select_key (matches, NULL, p, app, forced_valid);
      crypt_free_key (&matches);
      return k;
    }
  
  return NULL;
}