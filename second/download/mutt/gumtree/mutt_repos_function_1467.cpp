static int crypt_mod_pgp_verify_one (BODY *sigbdy, STATE *s, const char *tempf)
{
  return pgp_gpgme_verify_one (sigbdy, s, tempf);
}