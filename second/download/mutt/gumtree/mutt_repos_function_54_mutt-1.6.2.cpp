void crypt_smime_set_sender (const char *sender)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, set_sender))
    (CRYPT_MOD_CALL (SMIME, set_sender)) (sender);
}