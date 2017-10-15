	if (show_sig_summary (sum, ctx, key, idx, s, sig))
	  anywarn = 1;
      }
      else /* can't decide (yellow) */
      {
        print_smime_keyinfo (_("Problem signature from:"), sig, key, s);
        state_attach_puts (_("               expires: "), s);
        print_time (sig->exp_timestamp, s);
        state_attach_puts ("\n", s);
	show_sig_summary (sum, ctx, key, idx, s, sig);
        anywarn = 1;
      }

      if (key != signature_key)
	gpgme_key_release (key);
