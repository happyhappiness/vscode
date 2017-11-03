static int crypt_mod_pgp_application_handler (BODY *m, STATE *s)
{
  return pgp_gpgme_application_handler (m, s);
}