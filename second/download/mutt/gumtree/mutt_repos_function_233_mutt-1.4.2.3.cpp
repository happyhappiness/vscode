static BODY *pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
{
  BODY *b;

  char pgpoutfile[_POSIX_PATH_MAX];
  char pgperrfile[_POSIX_PATH_MAX];
  char pgpinfile[_POSIX_PATH_MAX];
  
  FILE *pgpout = NULL, *pgperr = NULL, *pgpin = NULL;
  FILE *fp;

  int empty;
  int err;

  char buff[STRING];

  pid_t thepid;
  
  if ((fp = fopen (a->filename, "r")) == NULL)
  {
    mutt_perror (a->filename);
    return NULL;
  }
  
  mutt_mktemp (pgpinfile);
  if ((pgpin = safe_fopen (pgpinfile, "w")) == NULL)
  {
    mutt_perror (pgpinfile);
    fclose (fp);
    return NULL;
  }

  mutt_copy_stream (fp, pgpin);
  fclose (fp);
  fclose (pgpin);

  mutt_mktemp (pgpoutfile);
  mutt_mktemp (pgperrfile);
  if ((pgpout = safe_fopen (pgpoutfile, "w+")) == NULL ||
      (pgperr = safe_fopen (pgperrfile, "w+")) == NULL)
  {
    mutt_perror (pgpout ? pgperrfile : pgpoutfile);
    unlink (pgpinfile);
    if (pgpout) 
    {
      fclose (pgpout);
      unlink (pgpoutfile);
    }
    return NULL;
  }
  
  unlink (pgperrfile);
  
  if ((thepid = pgp_invoke_traditional (&pgpin, NULL, NULL, 
					-1, fileno (pgpout), fileno (pgperr),
					pgpinfile, keylist, flags)) == -1)
  {
    mutt_perror _("Can't invoke PGP");
    fclose (pgpout);
    fclose (pgperr);
    mutt_unlink (pgpinfile);
    unlink (pgpoutfile);
    return NULL;
  }

  if (flags & PGPSIGN)
    fprintf (pgpin, "%s\n", PgpPass);
  fclose (pgpin);

  mutt_wait_filter (thepid);

  mutt_unlink (pgpinfile);

  fflush (pgpout);
  fflush (pgperr);

  rewind (pgpout);
  rewind (pgperr);
  
  empty = (fgetc (pgpout) == EOF);
  fclose (pgpout);
  
  err = 0;
  
  while (fgets (buff, sizeof (buff), pgperr))
  {
    err = 1;
    fputs (buff, stdout);
  }
  
  fclose (pgperr);
  
  if (err)
    mutt_any_key_to_continue (NULL);
  
  if (empty)
  {
    unlink (pgpoutfile);
    return NULL;
  }
    
  b = mutt_new_body ();
  
  b->encoding = ENC7BIT;

  b->type = TYPEAPPLICATION;
  b->subtype = safe_strdup ("pgp");

  mutt_set_parameter ("format", "text", &b->parameter);
  mutt_set_parameter ("x-action", flags & PGPENCRYPT ? "encrypt" : "sign",
		      &b->parameter);

  b->filename = safe_strdup (pgpoutfile);
  
  /* The following is intended to give a clue to some completely brain-dead 
   * "mail environments" which are typically used by large corporations.
   */

  b->d_filename = safe_strdup ("msg.pgp");
  b->disposition = DISPINLINE;
  b->unlink   = 1;
  b->use_disp = 1;

  return b;
}