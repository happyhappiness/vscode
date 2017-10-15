      }

      if (!s || !s->fpout || !(s->flags & M_DISPLAY))
	; /* No state information so no way to print anything. */
      else if (err)
	{
          snprintf (buf, sizeof (buf),
              _("Error getting key information for KeyID %s: %s\n"),
              fpr, gpgme_strerror (err));
          state_attach_puts (buf, s);
          anybad = 1;
	}
      else if ((sum & GPGME_SIGSUM_GREEN))
      {
        print_smime_keyinfo (_("Good signature from:"), sig, key, s);
	if (show_sig_summary (sum, ctx, key, idx, s, sig))
