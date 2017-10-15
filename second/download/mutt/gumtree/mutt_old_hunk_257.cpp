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
