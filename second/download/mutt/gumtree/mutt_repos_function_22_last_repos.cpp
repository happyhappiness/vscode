void crypt_init (void)
{
#ifdef CRYPT_BACKEND_CLASSIC_PGP
  if (
#ifdef CRYPT_BACKEND_GPGME
      (! option (OPTCRYPTUSEGPGME))
#else
       1
#endif
      )
    crypto_module_register (&crypt_mod_pgp_classic);
#endif

#ifdef CRYPT_BACKEND_CLASSIC_SMIME
  if (
#ifdef CRYPT_BACKEND_GPGME
      (! option (OPTCRYPTUSEGPGME))
#else
       1
#endif
      )
    crypto_module_register (&crypt_mod_smime_classic);
#endif

  if (option (OPTCRYPTUSEGPGME))
    {
#ifdef CRYPT_BACKEND_GPGME
      crypto_module_register (&crypt_mod_pgp_gpgme);
      crypto_module_register (&crypt_mod_smime_gpgme);
#else
      mutt_message (_("\"crypt_use_gpgme\" set"
                      " but not built with GPGME support."));
      if (mutt_any_key_to_continue (NULL) == -1)
	mutt_exit(1);
#endif
    }

#if defined CRYPT_BACKEND_CLASSIC_PGP || defined CRYPT_BACKEND_CLASSIC_SMIME || defined CRYPT_BACKEND_GPGME
  if (CRYPT_MOD_CALL_CHECK (PGP, init))
    (CRYPT_MOD_CALL (PGP, init)) ();

  if (CRYPT_MOD_CALL_CHECK (SMIME, init))
    (CRYPT_MOD_CALL (SMIME, init)) ();
#endif
}