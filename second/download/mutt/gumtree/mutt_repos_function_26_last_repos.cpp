int crypt_pgp_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, decrypt_mime))
    return (CRYPT_MOD_CALL (PGP, decrypt_mime)) (a, b, c, d);

  return -1;
}