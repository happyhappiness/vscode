static int crypt_id_is_valid (crypt_key_t *key)
{
  return ! (key->flags & KEYFLAG_CANTUSE);
}