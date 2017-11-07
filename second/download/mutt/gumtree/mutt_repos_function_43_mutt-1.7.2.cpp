int crypt_smime_decrypt_mime (FILE *a, FILE **b, BODY *c, BODY **d)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, decrypt_mime))
    return (CRYPT_MOD_CALL (SMIME, decrypt_mime)) (a, b, c, d);

  return -1;
}