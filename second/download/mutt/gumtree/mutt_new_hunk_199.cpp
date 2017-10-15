  
  dprint (2, (debugfile, "Entering pgp_encrypted handler\n"));

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fpout = safe_fopen (tempfile, "w+")))
    {
      if (s->flags & MUTT_DISPLAY)
        state_attach_puts (_("[-- Error: could not create temporary file! "
                             "--]\n"), s);
      return -1;
    }

  tattach = decrypt_part (a, s, fpout, 0, &is_signed);
  if (tattach)
    {
      tattach->goodsig = is_signed > 0;

      if (s->flags & MUTT_DISPLAY)
        state_attach_puts (is_signed?
          _("[-- The following data is PGP/MIME signed and encrypted --]\n\n"):
          _("[-- The following data is PGP/MIME encrypted --]\n\n"),
                           s);
      
      {
