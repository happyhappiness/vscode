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
