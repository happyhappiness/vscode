BODY *crypt_smime_sign_message (BODY *a)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, sign_message))
    return (CRYPT_MOD_CALL (SMIME, sign_message)) (a);

  return NULL;
}