void crypt_smime_getkeys (ENVELOPE *env)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, smime_getkeys))
    (CRYPT_MOD_CALL (SMIME, smime_getkeys)) (env);
}