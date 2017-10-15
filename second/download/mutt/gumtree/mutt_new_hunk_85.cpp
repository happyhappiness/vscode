    return -1;
  
  b = b->parts->next;
  
  memset (&s, 0, sizeof (s));
  s.fpin = fpin;
  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((*fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    return (-1);
  }
  unlink (tempfile);

  *cur = pgp_decrypt_part (b, &s, *fpout, p);

  rewind (*fpout);
  
  if (!*cur)
    return -1;
  
  return (0);
}

int pgp_encrypted_handler (BODY *a, STATE *s)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fpout, *fpin;
  BODY *tattach;
  BODY *p = a;
  int rc = 0;
  
  a = a->parts;
  if (!a || a->type != TYPEAPPLICATION || !a->subtype || 
      ascii_strcasecmp ("pgp-encrypted", a->subtype) != 0 ||
      !a->next || a->next->type != TYPEAPPLICATION || !a->next->subtype ||
      ascii_strcasecmp ("octet-stream", a->next->subtype) != 0)
  {
    if (s->flags & M_DISPLAY)
      state_attach_puts (_("[-- Error: malformed PGP/MIME message! --]\n\n"), s);
    return -1;
  }

  /*
   * Move forward to the application/pgp-encrypted body.
   */
  a = a->next;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    if (s->flags & M_DISPLAY)
      state_attach_puts (_("[-- Error: could not create temporary file! --]\n"), s);
    return -1;
  }

  if (s->flags & M_DISPLAY) crypt_current_time (s, "PGP");

  if ((tattach = pgp_decrypt_part (a, s, fpout, p)) != NULL)
  {
    if (s->flags & M_DISPLAY)
      state_attach_puts (_("[-- The following data is PGP/MIME encrypted --]\n\n"), s);

    fpin = s->fpin;
    s->fpin = fpout;
    rc = mutt_body_handler (tattach, s);
    s->fpin = fpin;

    /* 
     * if a multipart/signed is the _only_ sub-part of a
     * multipart/encrypted, cache signature verification
     * status.
