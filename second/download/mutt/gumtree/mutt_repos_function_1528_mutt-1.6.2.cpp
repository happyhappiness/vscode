int crypt_valid_passphrase(int flags)
{
  int ret = 0;

# if defined(HAVE_SETRLIMIT) &&(!defined(DEBUG))
  disable_coredumps ();
# endif

  if ((WithCrypto & APPLICATION_PGP) && (flags & APPLICATION_PGP))
    ret = crypt_pgp_valid_passphrase ();

  if ((WithCrypto & APPLICATION_SMIME) && (flags & APPLICATION_SMIME))
    ret = crypt_smime_valid_passphrase ();

  return ret;
}