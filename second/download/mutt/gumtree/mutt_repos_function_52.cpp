int crypt_smime_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, verify_one))
    return (CRYPT_MOD_CALL (SMIME, verify_one)) (sigbdy, s, tempf);

  return -1;
}