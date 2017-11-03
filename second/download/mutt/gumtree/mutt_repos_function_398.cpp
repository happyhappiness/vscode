static smime_key_t *smime_copy_key (smime_key_t *key)
{
  smime_key_t *copy;

  if (!key)
    return NULL;

  copy = safe_calloc (sizeof (smime_key_t), 1);
  copy->email  = safe_strdup(key->email);
  copy->hash   = safe_strdup(key->hash);
  copy->label  = safe_strdup(key->label);
  copy->issuer = safe_strdup(key->issuer);
  copy->trust  = key->trust;
  copy->flags  = key->flags;

  return copy;
}