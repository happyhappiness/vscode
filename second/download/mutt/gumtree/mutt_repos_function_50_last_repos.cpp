BODY *crypt_smime_build_smime_entity (BODY *a, char *certlist)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, smime_build_smime_entity))
    return (CRYPT_MOD_CALL (SMIME, smime_build_smime_entity)) (a, certlist);

  return NULL;
}