BODY *crypt_pgp_encrypt_message (BODY *a, char *keylist, int sign)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_encrypt_message))
    return (CRYPT_MOD_CALL (PGP, pgp_encrypt_message)) (a, keylist, sign);

  return NULL;
}