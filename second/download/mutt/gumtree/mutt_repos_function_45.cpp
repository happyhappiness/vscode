void crypt_smime_encrypted_handler (BODY *a, STATE *s)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, encrypted_handler))
    (CRYPT_MOD_CALL (SMIME, encrypted_handler)) (a, s);
}