static int crypt_mod_smime_application_handler (BODY *m, STATE *s)
{
  return smime_application_smime_handler (m, s);
}