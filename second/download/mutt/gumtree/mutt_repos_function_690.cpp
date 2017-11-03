static gpgme_ctx_t create_gpgme_context (int for_smime)
{
  gpgme_error_t err;
  gpgme_ctx_t ctx;

  err = gpgme_new (&ctx);
  if (err)
    {
      mutt_error (_("error creating gpgme context: %s\n"), gpgme_strerror (err));
      sleep (2);
      mutt_exit (1);
    }

  if (for_smime)
    {
      err = gpgme_set_protocol (ctx, GPGME_PROTOCOL_CMS);
      if (err)
        {
          mutt_error (_("error enabling CMS protocol: %s\n"),
                      gpgme_strerror (err));
          sleep (2);
          mutt_exit (1);
        }
    }

  return ctx;
}