BODY *crypt_pgp_sign_message (BODY *a)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, sign_message))
    return (CRYPT_MOD_CALL (PGP, sign_message)) (a);

  return NULL;
}