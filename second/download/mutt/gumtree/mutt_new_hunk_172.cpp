    fputs (buf, fpout);
  }

  safe_fclose (&pgpout);
  rv = mutt_wait_filter (thepid);
  mutt_unlink(pgptmpfile);

  fflush (pgperr);
  rewind (pgperr);
  if (pgp_check_decryption_okay (pgperr) < 0)
  {
    mutt_error _("Decryption failed");
    pgp_void_passphrase ();
    return NULL;
  }

  if (s->flags & M_DISPLAY)
  {
    rewind (pgperr);
    if (pgp_copy_checksig (pgperr, s->fpout) == 0 && !rv && p)
      p->goodsig = 1;
    else
      p->goodsig = 0;
    state_attach_puts (_("[-- End of PGP output --]\n\n"), s);
