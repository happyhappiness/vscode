static smime_key_t *smime_get_key_by_addr(char *mailbox, short abilities, short public, short may_ask)
{
  smime_key_t *results, *result;
  smime_key_t *matches = NULL;
  smime_key_t **matches_end = &matches;
  smime_key_t *match;
  smime_key_t *trusted_match = NULL;
  smime_key_t *valid_match = NULL;
  smime_key_t *return_key = NULL;
  int multi_trusted_matches = 0;

  if (! mailbox)
    return NULL;

  results = smime_get_candidates(mailbox, public);
  for (result = results; result; result = result->next)
  {
    if (abilities && !(result->flags & abilities))
    {
      continue;
    }

    if (mutt_strcasecmp (mailbox, result->email) == 0)
    {
      match = smime_copy_key (result);
      *matches_end = match;
      matches_end = &match->next;

      if (match->trust == 't')
      {
        if (trusted_match &&
            (mutt_strcasecmp (match->hash, trusted_match->hash) != 0))
        {
          multi_trusted_matches = 1;
        }
        trusted_match = match;
      }
      else if ((match->trust == 'u') || (match->trust == 'v'))
      {
        valid_match = match;
      }
    }
  }

  smime_free_key (&results);

  if (matches)
  {
    if (! may_ask)
    {
      if (trusted_match)
        return_key = smime_copy_key (trusted_match);
      else if (valid_match)
        return_key = smime_copy_key (valid_match);
      else
        return_key = NULL;
    }
    else if (trusted_match && !multi_trusted_matches)
    {
      return_key = smime_copy_key (trusted_match);
    }
    else
    {
      return_key = smime_copy_key (smime_select_key (matches, mailbox));
    }

    smime_free_key (&matches);
  }

  return return_key;
}