static int pgp_key_is_valid (pgp_key_t k)
{
  pgp_key_t pk = pgp_principal_key (k);
  if (k->flags & KEYFLAG_CANTUSE)
    return 0;
  if (pk->flags & KEYFLAG_CANTUSE)
    return 0;

  return 1;
}