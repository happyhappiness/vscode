int crypt_smime_valid_passphrase (void)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, valid_passphrase))
    return (CRYPT_MOD_CALL (SMIME, valid_passphrase)) ();

  return 0;
}