BODY *smime_build_smime_entity (BODY *a, char *certlist)
{
  char buf[LONG_STRING], certfile[LONG_STRING];
  char tempfile[_POSIX_PATH_MAX], smimeerrfile[_POSIX_PATH_MAX];
  char smimeinfile[_POSIX_PATH_MAX];
  char *cert_start, *cert_end;
  FILE *smimein = NULL, *smimeerr = NULL, *fpout = NULL, *fptmp = NULL;
  BODY *t;
  int err = 0, empty, off;
  pid_t thepid;
  
  mutt_mktemp (tempfile, sizeof (tempfile));
  if ((fpout = safe_fopen (tempfile, "w+")) == NULL)
  {
    mutt_perror (tempfile);
    return (NULL);
  }

  mutt_mktemp (smimeerrfile, sizeof (smimeerrfile));
  if ((smimeerr = safe_fopen (smimeerrfile, "w+")) == NULL)
  {
    mutt_perror (smimeerrfile);
    safe_fclose (&fpout);
    mutt_unlink (tempfile);
    return NULL;
  }
  mutt_unlink (smimeerrfile);
  
  mutt_mktemp (smimeinfile, sizeof (smimeinfile));
  if ((fptmp = safe_fopen (smimeinfile, "w+")) == NULL)
  {
    mutt_perror (smimeinfile);
    mutt_unlink (tempfile);
    safe_fclose (&fpout);
    safe_fclose (&smimeerr);
    return NULL;
  }

  *certfile = '\0';
  for (cert_start = certlist; cert_start; cert_start = cert_end)
  {
    if ((cert_end = strchr (cert_start, ' ')))
      *cert_end = '\0';
    if (*cert_start)
    {
      off = mutt_strlen (certfile);
      snprintf (certfile+off, sizeof (certfile)-off, "%s%s/%s",
                off ? " " : "", NONULL(SmimeCertificates), cert_start);
    }
    if (cert_end)
      *cert_end++ = ' ';
  }

  /* write a MIME entity */
  mutt_write_mime_header (a, fptmp);
  fputc ('\n', fptmp);
  mutt_write_mime_body (a, fptmp);
  safe_fclose (&fptmp);

  if ((thepid =
       smime_invoke_encrypt (&smimein, NULL, NULL, -1,
			     fileno (fpout), fileno (smimeerr),
			     smimeinfile, certfile)) == -1)
  {
    safe_fclose (&smimeerr);
    mutt_unlink (smimeinfile);
    mutt_unlink (certfile);
    return (NULL);
  }

  safe_fclose (&smimein);
  
  mutt_wait_filter (thepid);
  mutt_unlink (smimeinfile);
  mutt_unlink (certfile);
  
  fflush (fpout);
  rewind (fpout);
  empty = (fgetc (fpout) == EOF);
  safe_fclose (&fpout);
 
  fflush (smimeerr);
  rewind (smimeerr);
  while (fgets (buf, sizeof (buf) - 1, smimeerr) != NULL)
  {
    err = 1;
    fputs (buf, stdout);
  }
  safe_fclose (&smimeerr);

  /* pause if there is any error output from SMIME */
  if (err)
    mutt_any_key_to_continue (NULL);

  if (empty)
  {
    /* fatal error while trying to encrypt message */
    if (!err) mutt_any_key_to_continue _("No output from OpenSSL...");
    mutt_unlink (tempfile);
    return (NULL);
  }

  t = mutt_new_body ();
  t->type = TYPEAPPLICATION;
  t->subtype = safe_strdup ("x-pkcs7-mime");
  mutt_set_parameter ("name", "smime.p7m", &t->parameter);
  mutt_set_parameter ("smime-type", "enveloped-data", &t->parameter);
  t->encoding = ENCBASE64;  /* The output of OpenSSL SHOULD be binary */
  t->use_disp = 1;
  t->disposition = DISPATTACH;
  t->d_filename = safe_strdup ("smime.p7m");
  t->filename = safe_strdup (tempfile);
  t->unlink = 1; /*delete after sending the message */
  t->parts=0;
  t->next=0;
  
  return (t);
}