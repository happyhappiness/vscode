BODY *crypt_pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_traditional_encryptsign))
    return (CRYPT_MOD_CALL (PGP, pgp_traditional_encryptsign)) (a, flags, keylist);

  return NULL;
}