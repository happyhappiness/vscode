  struct stat info;
  BODY *tattach;
  int len;
  char pgperrfile[_POSIX_PATH_MAX];
  char pgptmpfile[_POSIX_PATH_MAX];
  pid_t thepid;
  int rv;
  
  mutt_mktemp (pgperrfile, sizeof (pgperrfile));
  if ((pgperr = safe_fopen (pgperrfile, "w+")) == NULL)
  {
    mutt_perror (pgperrfile);
    return NULL;
  }
  unlink (pgperrfile);

  mutt_mktemp (pgptmpfile, sizeof (pgptmpfile));
  if((pgptmp = safe_fopen (pgptmpfile, "w")) == NULL)
  {
    mutt_perror (pgptmpfile);
    safe_fclose (&pgperr);
    return NULL;
  }

  /* Position the stream at the beginning of the body, and send the data to
   * the temporary file.
   */

  fseeko (s->fpin, a->offset, 0);
  mutt_copy_bytes (s->fpin, pgptmp, a->length);
  safe_fclose (&pgptmp);

  if ((thepid = pgp_invoke_decrypt (&pgpin, &pgpout, NULL, -1, -1,
				    fileno (pgperr), pgptmpfile)) == -1)
  {
    safe_fclose (&pgperr);
    unlink (pgptmpfile);
    if (s->flags & M_DISPLAY)
      state_attach_puts (_("[-- Error: could not create a PGP subprocess! --]\n\n"), s);
    return (NULL);
  }

  /* send the PGP passphrase to the subprocess.  Never do this if the
     agent is active, because this might lead to a passphrase send as
     the message. */
  if (!pgp_use_gpg_agent())
    fputs (PgpPass, pgpin);
  fputc ('\n', pgpin);
  safe_fclose (&pgpin);
  
  /* Read the output from PGP, and make sure to change CRLF to LF, otherwise
   * read_mime_header has a hard time parsing the message.
   */
  while (fgets (buf, sizeof (buf) - 1, pgpout) != NULL)
  {
    len = mutt_strlen (buf);
    if (len > 1 && buf[len - 2] == '\r')
      strcpy (buf + len - 2, "\n");	/* __STRCPY_CHECKED__ */
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
  }
  safe_fclose (&pgperr);

  fflush (fpout);
  rewind (fpout);

  if (pgp_use_gpg_agent())
    mutt_need_hard_redraw ();

  if (fgetc (fpout) == EOF)
  {
    mutt_error _("Decryption failed");
    pgp_void_passphrase ();
    return NULL;
  }

  rewind (fpout);
  
  if ((tattach = mutt_read_mime_header (fpout, 0)) != NULL)
  {
    /*
     * Need to set the length of this body part.
     */
    fstat (fileno (fpout), &info);
