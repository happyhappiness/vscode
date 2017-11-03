static int crypt_key_is_valid (crypt_key_t *k)
{
  if (k->flags & KEYFLAG_CANTUSE)
    return 0;
  return 1;
}