void crypt_pgp_void_passphrase (void)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, void_passphrase))
    (CRYPT_MOD_CALL (PGP, void_passphrase)) ();
}