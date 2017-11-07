int pgp_encrypted_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fpout, *fpin;
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

    /* 
     * if a multipart/signed is the _only_ sub-part of a
     * multipart/encrypted, cache signature verification
     * status.
     *
     */
    
    if (mutt_is_multipart_signed (tattach) && !tattach->next)
      a->goodsig |= tattach->goodsig;
    
    if (s->flags & MUTT_DISPLAY)
    {
      state_puts ("\n", s);
      state_attach_puts (_("[-- End of PGP/MIME encrypted data --]\n"), s);
    }

    mutt_free_body (&tattach);
    /* clear 'Invoking...' message, since there's no error */
    mutt_message _("PGP message successfully decrypted.");
  }
  else
  {
    mutt_error _("Could not decrypt PGP message");
    mutt_sleep (2);
    /* void the passphrase, even if it's not necessarily the problem */
    pgp_void_passphrase ();
    rc = -1;
  }

  safe_fclose (&fpout);
  mutt_unlink(tempfile);

  return rc;
}