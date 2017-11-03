static int crypt_mod_pgp_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  return pgp_gpgme_decrypt_mime (a, b, c, d);
}