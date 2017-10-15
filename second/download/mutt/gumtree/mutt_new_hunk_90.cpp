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

BODY *pgp_traditional_encryptsign (BODY *a, int flags, char *keylist)
{
  BODY *b;

  char pgpoutfile[_POSIX_PATH_MAX];
  char pgperrfile[_POSIX_PATH_MAX];
  char pgpinfile[_POSIX_PATH_MAX];
  
  char body_charset[STRING];
  char *from_charset;
  const char *send_charset;
  
  FILE *pgpout = NULL, *pgperr = NULL, *pgpin = NULL;
  FILE *fp;

  int empty = 0;
  int err;

  char buff[STRING];

  pid_t thepid;

  if (a->type != TYPETEXT)
    return NULL;
  if (ascii_strcasecmp (a->subtype, "plain"))
    return NULL;
  
  if ((fp = fopen (a->filename, "r")) == NULL)
  {
    mutt_perror (a->filename);
    return NULL;
  }
  
  mutt_mktemp (pgpinfile, sizeof (pgpinfile));
  if ((pgpin = safe_fopen (pgpinfile, "w")) == NULL)
  {
    mutt_perror (pgpinfile);
    safe_fclose (&fp);
    return NULL;
  }

  /* The following code is really correct:  If noconv is set,
   * a's charset parameter contains the on-disk character set, and
   * we have to convert from that to utf-8.  If noconv is not set,
   * we have to convert from $charset to utf-8.
   */
  
  mutt_get_body_charset (body_charset, sizeof (body_charset), a);
  if (a->noconv)
    from_charset = body_charset;
  else 
    from_charset = Charset;
    
  if (!mutt_is_us_ascii (body_charset))
  {
    int c;
    FGETCONV *fc;
    
    if (flags & ENCRYPT)
      send_charset = "us-ascii";
    else
      send_charset = "utf-8";

    /* fromcode is assumed to be correct: we set flags to 0 */
    fc = fgetconv_open (fp, from_charset, "utf-8", 0);
    while ((c = fgetconv (fc)) != EOF)
      fputc (c, pgpin);
    
    fgetconv_close (&fc);
  }
  else
  {
    send_charset = "us-ascii";
    mutt_copy_stream (fp, pgpin);
  }
  safe_fclose (&fp);
  safe_fclose (&pgpin);

  mutt_mktemp (pgpoutfile, sizeof (pgpoutfile));
  mutt_mktemp (pgperrfile, sizeof (pgperrfile));
  if ((pgpout = safe_fopen (pgpoutfile, "w+")) == NULL ||
      (pgperr = safe_fopen (pgperrfile, "w+")) == NULL)
  {
    mutt_perror (pgpout ? pgperrfile : pgpoutfile);
    unlink (pgpinfile);
    if (pgpout) 
    {
      safe_fclose (&pgpout);
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
    safe_fclose (&pgpout);
    safe_fclose (&pgperr);
    mutt_unlink (pgpinfile);
    unlink (pgpoutfile);
    return NULL;
  }

  if (pgp_use_gpg_agent())
    *PgpPass = 0;
  if (flags & SIGN)
    fprintf (pgpin, "%s\n", PgpPass);
  safe_fclose (&pgpin);

  if(mutt_wait_filter (thepid) && option(OPTPGPCHECKEXIT))
    empty=1;

  mutt_unlink (pgpinfile);

  fflush (pgpout);
  fflush (pgperr);

  rewind (pgpout);
  rewind (pgperr);
  
  if(!empty)
    empty = (fgetc (pgpout) == EOF);
  safe_fclose (&pgpout);
  
  err = 0;
  
  while (fgets (buff, sizeof (buff), pgperr))
  {
    err = 1;
    fputs (buff, stdout);
  }
  
  safe_fclose (&pgperr);
  
  if (err)
    mutt_any_key_to_continue (NULL);
  
  if (empty)
  {
    if (flags & SIGN)
      pgp_void_passphrase (); /* just in case */
    unlink (pgpoutfile);
    return NULL;
  }
    
  b = mutt_new_body ();
  
  b->encoding = ENC7BIT;

  b->type = TYPETEXT;
  b->subtype = safe_strdup ("plain");
  
  mutt_set_parameter ("x-action", flags & ENCRYPT ? "pgp-encrypted" : "pgp-signed",
		      &b->parameter);
  mutt_set_parameter ("charset", send_charset, &b->parameter);
  
  b->filename = safe_strdup (pgpoutfile);
  
#if 0
  /* The following is intended to give a clue to some completely brain-dead 
   * "mail environments" which are typically used by large corporations.
   */

  b->d_filename = safe_strdup ("msg.pgp");
  b->use_disp = 1;

#endif

  b->disposition = DISPNONE;
  b->unlink   = 1;

  b->noconv = 1;
  b->use_disp = 0;
  
  if (!(flags & ENCRYPT))
    b->encoding = a->encoding;
  
  return b;
}

int pgp_send_menu (HEADER *msg, int *redraw)
{
  int choice;
  
  if (!(WithCrypto & APPLICATION_PGP))
    return msg->security;

  /* If autoinline and no crypto options set, then set inline. */
  if (option (OPTPGPAUTOINLINE) && 
      !((msg->security & APPLICATION_PGP) && (msg->security & (SIGN|ENCRYPT))))
    msg->security |= INLINE;
  
  /* When the message is not selected for signing or encryption, the toggle
   * between PGP/MIME and Traditional doesn't make sense.
   */
  if (msg->security & (ENCRYPT | SIGN))
  {
    char prompt[LONG_STRING];

    snprintf (prompt, sizeof (prompt), 
	_("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, %s format, or (c)lear? "),
	(msg->security & INLINE) ? _("PGP/M(i)ME") : _("(i)nline"));

    /* The keys accepted for this prompt *must* match the order in the second
     * version in the else clause since the switch statement below depends on
     * it.  The 'i' key is appended in this version.
     */
    choice = mutt_multi_choice (prompt, _("esabfci"));
  }
  else
  {
    /* The keys accepted *must* be a prefix of the accepted keys in the "if"
     * clause above since the switch statement below depends on it.
     */
    choice = mutt_multi_choice(_("PGP (e)ncrypt, (s)ign, sign (a)s, (b)oth, or (c)lear? "),
	_("esabfc"));
  }

  switch (choice)
  {
    case 1: /* (e)ncrypt */
      msg->security |= ENCRYPT;
      msg->security &= ~SIGN;
      break;

  case 2: /* (s)ign */
    msg->security |= SIGN;
    msg->security &= ~ENCRYPT;
    break;

  case 3: /* sign (a)s */
    {
      pgp_key_t p;
      char input_signas[SHORT_STRING];

      unset_option(OPTPGPCHECKTRUST);

      if ((p = pgp_ask_for_key (_("Sign as: "), NULL, 0, PGP_SECRING)))
      {
	snprintf (input_signas, sizeof (input_signas), "0x%s",
	    pgp_keyid (p));
	mutt_str_replace (&PgpSignAs, input_signas);
	pgp_free_key (&p);

	msg->security |= SIGN;

	crypt_pgp_void_passphrase ();  /* probably need a different passphrase */
      }
#if 0
      else
      {
	msg->security &= ~SIGN;
      }
#endif

      *redraw = REDRAW_FULL;
    } break;

  case 4: /* (b)oth */
    msg->security |= (ENCRYPT | SIGN);
    break;

  case 5: /* (f)orget it */
  case 6: /* (c)lear     */
    msg->security = 0;
    break;

  case 7: /* toggle (i)nline */
    msg->security ^= INLINE;
    break;
  }

  if (msg->security)
  {
    if (! (msg->security & (ENCRYPT | SIGN)))
      msg->security = 0;
    else
      msg->security |= APPLICATION_PGP;
  }

  return (msg->security);
}


#endif /* CRYPT_BACKEND_CLASSIC_PGP */
