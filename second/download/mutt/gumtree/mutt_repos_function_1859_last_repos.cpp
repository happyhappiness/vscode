static int crypt_mod_smime_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  return smime_gpgme_verify_one (sigbdy, s, tempf);
}