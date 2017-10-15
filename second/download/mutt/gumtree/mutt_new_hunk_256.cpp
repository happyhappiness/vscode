                              STATE *s, gpgme_signature_t sig)
{
  int severe = 0;

  if ((sum & GPGME_SIGSUM_KEY_REVOKED))
    {
      state_puts (_("Warning: One of the keys has been revoked\n"),s);
      severe = 1;
    }

  if ((sum & GPGME_SIGSUM_KEY_EXPIRED))
    {
      time_t at = key->subkeys->expires ? key->subkeys->expires : 0;
      if (at)
        {
          state_puts (_("Warning: The key used to create the "
                               "signature expired at: "), s);
          print_time (at , s);
          state_puts ("\n", s);
        }
      else
        state_puts (_("Warning: At least one certification key "
                             "has expired\n"), s);
    }

  if ((sum & GPGME_SIGSUM_SIG_EXPIRED))
    {
      gpgme_verify_result_t result;
