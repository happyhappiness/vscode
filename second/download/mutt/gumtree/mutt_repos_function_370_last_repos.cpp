static int crypt_mod_pgp_application_handler (BODY *m, STATE *s)
{
  return pgp_application_pgp_handler (m, s);
}