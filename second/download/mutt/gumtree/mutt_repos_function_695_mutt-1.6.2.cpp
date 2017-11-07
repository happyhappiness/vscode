int pgp_gpgme_verify_one (BODY *sigbdy, STATE *s, const char *tempfile)
{
  return verify_one (sigbdy, s, tempfile, 0);
}