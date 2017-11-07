static BODY *crypt_mod_pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
{
  return pgp_traditional_encryptsign (a, flags, keylist);
}