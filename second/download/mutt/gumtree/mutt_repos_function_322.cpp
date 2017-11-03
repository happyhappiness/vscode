BODY *pgp_sign_message (BODY *a)
{
  BODY *t;
  char buffer[LONG_STRING];
  char sigfile[_POSIX_PATH_MAX], signedfile[_POSIX_PATH_MAX];
  FILE *pgpin, *pgpout, *pgperr, *fp, *sfp;
  int err = 0;
  int empty = 1;
  pid_t thepid;
  
  convert_to_7bit (a); /* Signed data _must_ be in 7-bit format. */

  mutt_mktemp (sigfile, sizeof (sigfile));
  if ((fp = safe_fopen (sigfile, "w")) == NULL)
  {
    return (NULL);
  }

  mutt_mktemp (signedfile, sizeof (signedfile));
  if ((sfp = safe_fopen(signedfile, "w")) == NULL)
  {
    mutt_perror(signedfile);
    safe_fclose (&fp);
    unlink(sigfile);
    return NULL;
  }
  
  mutt_write_mime_header (a, sfp);
  fputc ('\n', sfp);
  mutt_write_mime_body (a, sfp);
  safe_fclose (&sfp);
  
  if ((thepid = pgp_invoke_sign (&pgpin, &pgpout, &pgperr,
				 -1, -1, -1, signedfile)) == -1)
  {
    mutt_perror _("Can't open PGP subprocess!");
    safe_fclose (&fp);
    unlink(sigfile);
    unlink(signedfile);
    return NULL;
  }
  
  if (!pgp_use_gpg_agent())
     fputs(PgpPass, pgpin);
  fputc('\n', pgpin);
  safe_fclose (&pgpin);
  
  /*
   * Read back the PGP signature.  Also, change MESSAGE=>SIGNATURE as
   * recommended for future releases of PGP.
   */
  while (fgets (buffer, sizeof (buffer) - 1, pgpout) != NULL)
  {
    if (mutt_strcmp ("-----BEGIN PGP MESSAGE-----\n", buffer) == 0)
      fputs ("-----BEGIN PGP SIGNATURE-----\n", fp);
    else if (mutt_strcmp("-----END PGP MESSAGE-----\n", buffer) == 0)
      fputs ("-----END PGP SIGNATURE-----\n", fp);
    else
      fputs (buffer, fp);
    empty = 0; /* got some output, so we're ok */
  }

  /* check for errors from PGP */
  err = 0;
  while (fgets (buffer, sizeof (buffer) - 1, pgperr) != NULL)
  {
    err = 1;
    fputs (buffer, stdout);
  }

  if(mutt_wait_filter (thepid) && option(OPTPGPCHECKEXIT))
    empty=1;

  safe_fclose (&pgperr);
  safe_fclose (&pgpout);
  unlink (signedfile);
  
  if (fclose (fp) != 0)
  {
    mutt_perror ("fclose");
    unlink (sigfile);
    return (NULL);
  }

  if (err)
    mutt_any_key_to_continue (NULL);
  if (empty)
  {
    unlink (sigfile);
    /* most likely error is a bad passphrase, so automatically forget it */
    pgp_void_passphrase ();
    return (NULL); /* fatal error while signing */
  }

  t = mutt_new_body ();
  t->type = TYPEMULTIPART;
  t->subtype = safe_strdup ("signed");
  t->encoding = ENC7BIT;
  t->use_disp = 0;
  t->disposition = DISPINLINE;

  mutt_generate_boundary (&t->parameter);
  mutt_set_parameter ("protocol", "application/pgp-signature", &t->parameter);
  mutt_set_parameter ("micalg", pgp_micalg (sigfile), &t->parameter);

  t->parts = a;
  a = t;

  t->parts->next = mutt_new_body ();
  t = t->parts->next;
  t->type = TYPEAPPLICATION;
  t->subtype = safe_strdup ("pgp-signature");
  t->filename = safe_strdup (sigfile);
  t->use_disp = 0;
  t->disposition = DISPNONE;
  t->encoding = ENC7BIT;
  t->unlink = 1; /* ok to remove this file after sending. */
  mutt_set_parameter ("name", "signature.asc", &t->parameter);

  return (a);
}