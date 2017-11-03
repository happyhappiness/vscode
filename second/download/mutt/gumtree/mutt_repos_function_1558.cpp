void crypt_forget_passphrase (void)
{
  if ((WithCrypto & APPLICATION_PGP))
    crypt_pgp_void_passphrase ();

  if ((WithCrypto & APPLICATION_SMIME))
    crypt_smime_void_passphrase ();

  if (WithCrypto)
    mutt_message _("Passphrase(s) forgotten.");
}