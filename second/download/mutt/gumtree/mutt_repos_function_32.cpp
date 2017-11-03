BODY *crypt_pgp_make_key_attachment (char *tempf)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_make_key_attachment))
    return (CRYPT_MOD_CALL (PGP, pgp_make_key_attachment)) (tempf);

  return NULL;
}