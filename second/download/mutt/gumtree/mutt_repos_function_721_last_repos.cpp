static gpgme_error_t
set_pka_sig_notation (gpgme_ctx_t ctx)
{
  gpgme_error_t err;

  err = gpgme_sig_notation_add (ctx,
				PKA_NOTATION_NAME, current_sender, 0);

  if (err)
    {
      mutt_error (_("error setting PKA signature notation: %s\n"),
		  gpgme_strerror (err));
      mutt_sleep (2);
    }

  return err;
}