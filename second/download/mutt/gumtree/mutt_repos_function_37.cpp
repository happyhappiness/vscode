int crypt_pgp_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, verify_one))
    return (CRYPT_MOD_CALL (PGP, verify_one)) (sigbdy, s, tempf);

  return -1;
}