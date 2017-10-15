  t->parts->next = mutt_new_body ();
  t->parts->next->type = TYPEAPPLICATION;
  t->parts->next->subtype = safe_strdup ("octet-stream");
  t->parts->next->encoding = ENC7BIT;
  t->parts->next->filename = safe_strdup (tempfile);
  t->parts->next->use_disp = 1;
  t->parts->next->disposition = DISPINLINE;
  t->parts->next->unlink = 1; /* delete after sending the message */
  t->parts->next->d_filename = safe_strdup ("msg.asc"); /* non pgp/mime can save */

  return (t);
}

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



int pgp_get_keys (HEADER *msg, char **pgpkeylist)
{
  /* Do a quick check to make sure that we can find all of the encryption
   * keys if the user has requested this service.
   */

  set_option (OPTPGPCHECKTRUST);

  *pgpkeylist = NULL;
  if (msg->pgp & PGPENCRYPT)
  {
    if ((*pgpkeylist = pgp_findKeys (msg->env->to, msg->env->cc,
				      msg->env->bcc)) == NULL)
      return (-1);
  }

  return (0);
}

int pgp_protect (HEADER *msg, char *pgpkeylist)
{
  BODY *pbody = NULL;
  int flags = msg->pgp;
  int traditional = 0;
  int i;

  if ((msg->pgp & PGPSIGN) && !pgp_valid_passphrase ())
    return (-1);

  if ((msg->content->type == TYPETEXT) &&
      !ascii_strcasecmp (msg->content->subtype, "plain") &&
      ((flags & PGPENCRYPT) || (msg->content->content && msg->content->content->hibin == 0)))
  {
    if ((i = query_quadoption (OPT_PGPTRADITIONAL, _("Create an application/pgp message?"))) == -1)
      return -1;
    else if (i == M_YES)
      traditional = 1;
  }

  mutt_message _("Invoking PGP...");

  if (!isendwin ())
    mutt_endwin (NULL);

  if (traditional)
  {
    if (!(pbody = pgp_traditional_encryptsign (msg->content, flags, pgpkeylist)))
      return -1;
    
    msg->content = pbody;
    return 0;
  }

  if ((flags & PGPSIGN) && (!(flags & PGPENCRYPT) || option (OPTPGPRETAINABLESIG)))
  {
    if (!(pbody = pgp_sign_message (msg->content)))
      return -1;

    msg->content = pbody;
    flags &= ~PGPSIGN;
  }

  if (flags & PGPENCRYPT)
  {
    if (!(pbody = pgp_encrypt_message (msg->content, pgpkeylist, flags & PGPSIGN)))
    {

      /* did we perform a retainable signature? */
      if (flags != msg->pgp)
      {
	/* remove the outer multipart layer */
	msg->content = mutt_remove_multipart (msg->content);
	/* get rid of the signature */
	mutt_free_body (&msg->content->next);
      }

      return (-1);
    }

    /* destroy temporary signature envelope when doing retainable 
     * signatures.
     */
    if (flags != msg->pgp)
    {
      mutt_remove_multipart (msg->content);
      mutt_free_body (&msg->content->next);
    }
    
    msg->content = pbody;
  }

  return (0);
}

#endif /* HAVE_PGP */
