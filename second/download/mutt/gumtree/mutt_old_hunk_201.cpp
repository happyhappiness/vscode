  dprint (2, (debugfile, "Entering smime_encrypted handler\n"));
  
  a->warnsig = 0;
  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fpout = safe_fopen (tempfile, "w+")))
    {
      if (s->flags & M_DISPLAY)
        state_attach_puts (_("[-- Error: could not create temporary file! "
                             "--]\n"), s);
      return -1;
    }

  tattach = decrypt_part (a, s, fpout, 1, &is_signed);
  if (tattach)
    {
      tattach->goodsig = is_signed > 0;

      if (s->flags & M_DISPLAY)
        state_attach_puts (is_signed?
          _("[-- The following data is S/MIME signed --]\n\n"):
          _("[-- The following data is S/MIME encrypted --]\n\n"),
                           s);
      
      {
