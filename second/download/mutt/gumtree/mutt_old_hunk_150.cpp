      }

      if (!s || !s->fpout || !(s->flags & M_DISPLAY))
	; /* No state information so no way to print anything. */
      else if (err)
	{
          state_attach_puts (_("Error getting key information for KeyID "), s);
	  state_attach_puts ( fpr, s );
          state_attach_puts (_(": "), s);
          state_attach_puts ( gpgme_strerror (err), s );
          state_attach_puts ("\n", s);
          anybad = 1;
	}
      else if ((sum & GPGME_SIGSUM_GREEN))
      {
        print_smime_keyinfo (_("Good signature from:"), sig, key, s);
	if (show_sig_summary (sum, ctx, key, idx, s, sig))
