int crypt_smime_application_smime_handler (BODY *m, STATE *s)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, application_handler))
    return (CRYPT_MOD_CALL (SMIME, application_handler)) (m, s);
  
  return -1;
}