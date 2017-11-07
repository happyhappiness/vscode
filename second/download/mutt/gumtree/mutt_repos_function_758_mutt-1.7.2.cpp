static void init_pgp (void)
{
  if (gpgme_engine_check_version (GPGME_PROTOCOL_OpenPGP) != GPG_ERR_NO_ERROR)
  {
    mutt_error (_("GPGME: OpenPGP protocol not available"));
  }
}