  BODY *tattach;
  int rc = 0;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    if (s->flags & MUTT_DISPLAY)
      state_attach_puts (_("[-- Error: could not create temporary file! --]\n"), s);
    return -1;
  }

  if (s->flags & MUTT_DISPLAY) crypt_current_time (s, "PGP");

  if ((tattach = pgp_decrypt_part (a, s, fpout, a)) != NULL)
  {
    if (s->flags & MUTT_DISPLAY)
      state_attach_puts (_("[-- The following data is PGP/MIME encrypted --]\n\n"), s);

    fpin = s->fpin;
    s->fpin = fpout;
    rc = mutt_body_handler (tattach, s);
    s->fpin = fpin;
