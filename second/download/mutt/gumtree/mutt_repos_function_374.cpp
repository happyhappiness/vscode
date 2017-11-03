static int crypt_mod_pgp_encrypted_handler (BODY *m, STATE *s)
{
  return pgp_encrypted_handler (m, s);
}