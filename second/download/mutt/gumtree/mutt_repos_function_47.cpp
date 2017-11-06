int crypt_smime_verify_sender(HEADER *h)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, smime_verify_sender))
    return (CRYPT_MOD_CALL (SMIME, smime_verify_sender)) (h);

  return 1;
}