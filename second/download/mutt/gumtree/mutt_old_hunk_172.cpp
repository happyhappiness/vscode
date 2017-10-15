    fputs (buf, fpout);
  }

  safe_fclose (&pgpout);
  rv = mutt_wait_filter (thepid);
  mutt_unlink(pgptmpfile);
  
  if (s->flags & M_DISPLAY)
  {
    fflush (pgperr);
    rewind (pgperr);
    if (pgp_copy_checksig (pgperr, s->fpout) == 0 && !rv && p)
      p->goodsig = 1;
    else
      p->goodsig = 0;
    state_attach_puts (_("[-- End of PGP output --]\n\n"), s);
