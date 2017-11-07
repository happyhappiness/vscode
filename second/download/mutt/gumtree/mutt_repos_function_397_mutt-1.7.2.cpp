void smime_free_key (smime_key_t **keylist)
{
  smime_key_t *key;

  if (!keylist)
    return;

  while (*keylist)
  {
    key = *keylist;
    *keylist = (*keylist)->next;

    FREE (&key->email);
    FREE (&key->hash);
    FREE (&key->label);
    FREE (&key->issuer);
    FREE (&key);
  }
}