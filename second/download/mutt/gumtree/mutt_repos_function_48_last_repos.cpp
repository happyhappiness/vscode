char *crypt_smime_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, findkeys))
    return (CRYPT_MOD_CALL (SMIME, findkeys)) (adrlist, oppenc_mode);

  return NULL;
}