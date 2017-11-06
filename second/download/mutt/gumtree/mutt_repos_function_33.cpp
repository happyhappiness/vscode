char *crypt_pgp_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, findkeys))
    return (CRYPT_MOD_CALL (PGP, findkeys)) (adrlist, oppenc_mode);

  return NULL;
}