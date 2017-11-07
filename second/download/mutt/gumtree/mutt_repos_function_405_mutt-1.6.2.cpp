static smime_key_t *smime_get_key_by_str(char *str, short abilities, short public)
{
  smime_key_t *results, *result;
  smime_key_t *matches = NULL;
  smime_key_t **matches_end = &matches;
  smime_key_t *match;
  smime_key_t *return_key = NULL;

  if (! str)
    return NULL;

  results = smime_get_candidates(str, public);
  for (result = results; result; result = result->next)
  {
    if (abilities && !(result->flags & abilities))
    {
      continue;
    }

    if ((mutt_strcasecmp (str, result->hash) == 0) ||
        mutt_stristr(result->email, str) ||
        mutt_stristr(result->label, str))
    {
      match = smime_copy_key (result);
      *matches_end = match;
      matches_end = &match->next;
    }
  }

  smime_free_key (&results);

  if (matches)
  {
    return_key = smime_copy_key (smime_select_key (matches, str));
    smime_free_key (&matches);
  }

  return return_key;
}