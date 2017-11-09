BODY *pgp_encrypt_message (BODY *a, char *keylist, int sign)
{
  char buf[LONG_STRING];
  char tempfile[_POSIX_PATH_MAX], pgperrfile[_POSIX_PATH_MAX];
  char pgpinfile[_POSIX_PATH_MAX];
  FILE *pgpin, *pgperr, *fpout, *fptmp;
  BODY *t;
  int err = 0;
  int empty = 0;
  pid_t thepid;
  
  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    return (NULL);
  }

  mutt_mktemp (pgperrfile, sizeof (pgperrfile));
  if ((pgperr = safe_fopen (pgperrfile, "w+")) == NULL)
  {
    mutt_perror (pgperrfile);
    unlink(tempfile);
    safe_fclose (&fpout);
    return NULL;
  }
  unlink (pgperrfile);

  mutt_mktemp (pgpinfile, sizeof (pgpinfile));
  if((fptmp = safe_fopen(pgpinfile, "w")) == NULL)
  {
    mutt_perror(pgpinfile);
    unlink(tempfile);
    safe_fclose (&fpout);
    safe_fclose (&pgperr);
    return NULL;
  }
  
  if (sign)
    convert_to_7bit (a);
  
  mutt_write_mime_header (a, fptmp);
  fputc ('\n', fptmp);
  mutt_write_mime_body (a, fptmp);
  safe_fclose (&fptmp);
  
  if ((thepid = pgp_invoke_encrypt (&pgpin, NULL, NULL, -1, 
				    fileno (fpout), fileno (pgperr),
				    pgpinfile, keylist, sign)) == -1)
  {
    safe_fclose (&pgperr);
    unlink(pgpinfile);
    return (NULL);
  }

  if (sign)
  {
    if (!pgp_use_gpg_agent())
       fputs (PgpPass, pgpin);
    fputc ('\n', pgpin);
  }
  safe_fclose (&pgpin);
  
  if(mutt_wait_filter (thepid) && option(OPTPGPCHECKEXIT))
    empty=1;

  unlink(pgpinfile);
  
  fflush (fpout);
  rewind (fpout);
  if(!empty)
    empty = (fgetc (fpout) == EOF);
  safe_fclose (&fpout);

  fflush (pgperr);
  rewind (pgperr);
  while (fgets (buf, sizeof (buf) - 1, pgperr) != NULL)
  {
    err = 1;
    fputs (buf, stdout);
  }
  safe_fclose (&pgperr);

  /* pause if there is any error output from PGP */
  if (err)
    mutt_any_key_to_continue (NULL);

  if (empty)
  {
    /* fatal error while trying to encrypt message */
    if (sign)
      pgp_void_passphrase (); /* just in case */
    unlink (tempfile);
    return (NULL);
  }

  t = mutt_new_body ();
  t->type = TYPEMULTIPART;
  t->subtype = safe_strdup ("encrypted");
  t->encoding = ENC7BIT;
  t->use_disp = 0;
  t->disposition = DISPINLINE;

  mutt_generate_boundary(&t->parameter);
  mutt_set_parameter("protocol", "application/pgp-encrypted", &t->parameter);
  
  t->parts = mutt_new_body ();
  t->parts->type = TYPEAPPLICATION;
  t->parts->subtype = safe_strdup ("pgp-encrypted");
  t->parts->encoding = ENC7BIT;

  t->parts->next = mutt_new_body ();
  t->parts->next->type = TYPEAPPLICATION;
  t->parts->next->subtype = safe_strdup ("octet-stream");
  t->parts->next->encoding = ENC7BIT;
  t->parts->next->filename = safe_strdup (tempfile);
  t->parts->next->use_disp = 1;
  t->parts->next->disposition = DISPATTACH;
  t->parts->next->unlink = 1; /* delete after sending the message */
  t->parts->next->d_filename = safe_strdup ("msg.asc"); /* non pgp/mime can save */

  return (t);
}