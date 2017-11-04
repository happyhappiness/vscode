static int show_sig_summary (unsigned long sum,
                              gpgme_ctx_t ctx, gpgme_key_t key, int idx,
                              STATE *s, gpgme_signature_t sig)
{
  int severe = 0;

  if ((sum & GPGME_SIGSUM_KEY_REVOKED))
    {
      state_attach_puts (_("Warning: One of the keys has been revoked\n"),s);
      severe = 1;
    }

  if ((sum & GPGME_SIGSUM_KEY_EXPIRED))
    {
      time_t at = key->subkeys->expires ? key->subkeys->expires : 0;
      if (at)
        {
          state_attach_puts (_("Warning: The key used to create the "
                               "signature expired at: "), s);
          print_time (at , s);
          state_attach_puts ("\n", s);
        }
      else
        state_attach_puts (_("Warning: At least one certification key "
                             "has expired\n"), s);
    }

  if ((sum & GPGME_SIGSUM_SIG_EXPIRED))
    {
      gpgme_verify_result_t result;
      gpgme_signature_t sig;
      unsigned int i;
      
      result = gpgme_op_verify_result (ctx);

      for (sig = result->signatures, i = 0; sig && (i < idx);
           sig = sig->next, i++)
        ;
      
      state_attach_puts (_("Warning: The signature expired at: "), s);
      print_time (sig ? sig->exp_timestamp : 0, s);
      state_attach_puts ("\n", s);
    }

  if ((sum & GPGME_SIGSUM_KEY_MISSING))
    state_attach_puts (_("Can't verify due to a missing "
                         "key or certificate\n"), s);

  if ((sum & GPGME_SIGSUM_CRL_MISSING))
    {
      state_attach_puts (_("The CRL is not available\n"), s);
      severe = 1;
    }

  if ((sum & GPGME_SIGSUM_CRL_TOO_OLD))
    {
      state_attach_puts (_("Available CRL is too old\n"), s);
      severe = 1;
    }

  if ((sum & GPGME_SIGSUM_BAD_POLICY))
    state_attach_puts (_("A policy requirement was not met\n"), s);

  if ((sum & GPGME_SIGSUM_SYS_ERROR))
    {
      const char *t0 = NULL, *t1 = NULL;
      gpgme_verify_result_t result;
      gpgme_signature_t sig;
      unsigned int i;

      state_attach_puts (_("A system error occurred"), s );

      /* Try to figure out some more detailed system error information. */
      result = gpgme_op_verify_result (ctx);
      for (sig = result->signatures, i = 0; sig && (i < idx);
           sig = sig->next, i++)
        ;
      if (sig)
	{
	  t0 = "";
	  t1 = sig->wrong_key_usage ? "Wrong_Key_Usage" : "";
	}

      if (t0 || t1)
        {
          state_attach_puts (": ", s);
          if (t0)
              state_attach_puts (t0, s);
          if (t1 && !(t0 && !strcmp (t0, t1)))
            {
              if (t0)
                state_attach_puts (",", s);
              state_attach_puts (t1, s);
            }
        }
      state_attach_puts ("\n", s);
    }

#ifdef HAVE_GPGME_PKA_TRUST

  if (option (OPTCRYPTUSEPKA))
    {
      if (sig->pka_trust == 1 && sig->pka_address)
	{
	  state_attach_puts (_("WARNING: PKA entry does not match "
			       "signer's address: "), s);
	  state_attach_puts (sig->pka_address, s);
	  state_attach_puts ("\n", s);
	}
      else if (sig->pka_trust == 2 && sig->pka_address)
	{
	  state_attach_puts (_("PKA verified signer's address is: "), s);
	  state_attach_puts (sig->pka_address, s);
	  state_attach_puts ("\n", s);
	}
    }

#endif

  return severe;
}