static int crypt_mod_smime_application_handler (BODY *m, STATE *s)
{
  return smime_gpgme_application_handler (m, s);
}