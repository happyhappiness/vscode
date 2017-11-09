void crypt_smime_void_passphrase (void)
{
  if (CRYPT_MOD_CALL_CHECK (SMIME, void_passphrase))
    (CRYPT_MOD_CALL (SMIME, void_passphrase)) ();
}