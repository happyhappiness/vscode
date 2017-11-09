static void init_smime (void)
{
  if (gpgme_engine_check_version (GPGME_PROTOCOL_CMS) != GPG_ERR_NO_ERROR)
  {
    mutt_error (_("GPGME: CMS protocol not available"));
  }
}