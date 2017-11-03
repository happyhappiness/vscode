static void crypt_free_key (crypt_key_t **keylist)
{
  crypt_key_t *k;

  if (!keylist)
    return;

  while (*keylist)
  {
    k = *keylist;
    *keylist = (*keylist)->next;

    gpgme_key_unref (k->kobj);
    FREE (&k);
  }
}