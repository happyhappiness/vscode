static crypt_key_t *crypt_copy_key (crypt_key_t *key)
{
  crypt_key_t *k;

  k = safe_calloc (1, sizeof *k);
  k->kobj = key->kobj;
  gpgme_key_ref (key->kobj);
  k->idx = key->idx;
  k->uid = key->uid;
  k->flags = key->flags;
  k->validity = key->validity;

  return k;
}