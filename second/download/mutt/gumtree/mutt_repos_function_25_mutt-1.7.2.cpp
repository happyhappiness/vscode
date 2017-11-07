int crypt_pgp_valid_passphrase (void)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, valid_passphrase))
    return (CRYPT_MOD_CALL (PGP, valid_passphrase)) ();

  return 0;
}