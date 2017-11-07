BODY *smime_sign_message (BODY *a )
{
  BODY *t;
  char buffer[LONG_STRING];
  char signedfile[_POSIX_PATH_MAX], filetosign[_POSIX_PATH_MAX];
  FILE *smimein = NULL, *smimeout = NULL, *smimeerr = NULL, *sfp = NULL;
  int err = 0;
  int empty = 0;
  pid_t thepid;
  smime_key_t *default_key;
  char *intermediates;
  char *micalg;

  if (!SmimeDefaultKey)
  {
    mutt_error _("Can't sign: No key specified. Use Sign As.");
    return NULL;
  }

  convert_to_7bit (a); /* Signed data _must_ be in 7-bit format. */

  mutt_mktemp (filetosign, sizeof (filetosign));
  if ((sfp = safe_fopen (filetosign, "w+")) == NULL)
  {
    mutt_perror (filetosign);
    return NULL;
  }

  mutt_mktemp (signedfile, sizeof (signedfile));
  if ((smimeout = safe_fopen (signedfile, "w+")) == NULL)
  {
    mutt_perror (signedfile);
    safe_fclose (&sfp);
    mutt_unlink (filetosign);
    return NULL;
  }
  
  mutt_write_mime_header (a, sfp);
  fputc ('\n', sfp);
  mutt_write_mime_body (a, sfp);
  safe_fclose (&sfp);

  

  snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	   NONULL(SmimeKeys), SmimeDefaultKey);

  snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	   NONULL(SmimeCertificates), SmimeDefaultKey);
  
  default_key = smime_get_key_by_hash (SmimeDefaultKey, 1);
  if ((! default_key) ||
      (! mutt_strcmp ("?", default_key->issuer)))
    intermediates = SmimeDefaultKey; /* so openssl won't complain in any case */
  else
    intermediates = default_key->issuer;

  snprintf (SmimeIntermediateToUse, sizeof (SmimeIntermediateToUse), "%s/%s",
	   NONULL(SmimeCertificates), intermediates);

  smime_free_key (&default_key);
  


  if ((thepid = smime_invoke_sign (&smimein, NULL, &smimeerr,
				 -1, fileno (smimeout), -1, filetosign)) == -1)
  {
    mutt_perror _("Can't open OpenSSL subprocess!");
    safe_fclose (&smimeout);
    mutt_unlink (signedfile);
    mutt_unlink (filetosign);
    return NULL;
  }
  fputs (SmimePass, smimein);
  fputc ('\n', smimein);
  safe_fclose (&smimein);
  

  mutt_wait_filter (thepid);

  /* check for errors from OpenSSL */
  err = 0;
  fflush (smimeerr);
  rewind (smimeerr);
  while (fgets (buffer, sizeof (buffer) - 1, smimeerr) != NULL)
  {
    err = 1;
    fputs (buffer, stdout);
  }
  safe_fclose (&smimeerr);


  fflush (smimeout);
  rewind (smimeout);
  empty = (fgetc (smimeout) == EOF);
  safe_fclose (&smimeout);

  mutt_unlink (filetosign);
  

  if (err)
    mutt_any_key_to_continue (NULL);

  if (empty)
  {
    mutt_any_key_to_continue _("No output from OpenSSL...");
    mutt_unlink (signedfile);
    return (NULL); /* fatal error while signing */
  }

  t = mutt_new_body ();
  t->type = TYPEMULTIPART;
  t->subtype = safe_strdup ("signed");
  t->encoding = ENC7BIT;
  t->use_disp = 0;
  t->disposition = DISPINLINE;

  mutt_generate_boundary (&t->parameter);

  micalg = openssl_md_to_smime_micalg (SmimeDigestAlg);
  mutt_set_parameter ("micalg", micalg, &t->parameter);
  FREE (&micalg);

  mutt_set_parameter ("protocol", "application/x-pkcs7-signature",
		     &t->parameter);

  t->parts = a;
  a = t;

  t->parts->next = mutt_new_body ();
  t = t->parts->next;
  t->type = TYPEAPPLICATION;
  t->subtype = safe_strdup ("x-pkcs7-signature");
  t->filename = safe_strdup (signedfile);
  t->d_filename = safe_strdup ("smime.p7s");
  t->use_disp = 1;
  t->disposition = DISPATTACH;
  t->encoding = ENCBASE64;
  t->unlink = 1; /* ok to remove this file after sending. */

  return (a);

}