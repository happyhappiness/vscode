static smime_key_t *smime_get_key_by_hash(char *hash, short public)
{
  smime_key_t *results, *result;
  smime_key_t *match = NULL;

  results = smime_get_candidates(hash, public);
  for (result = results; result; result = result->next)
  {
    if (mutt_strcasecmp (hash, result->hash) == 0)
    {
      match = smime_copy_key (result);
      break;
    }
  }

  smime_free_key (&results);

  return match;
}