static int crypt_mod_smime_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  return smime_gpgme_decrypt_mime (a, b, c, d);
}