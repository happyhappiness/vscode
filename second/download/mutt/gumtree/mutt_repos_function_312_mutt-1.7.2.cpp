int pgp_application_pgp_handler (BODY *m, STATE *s)
{
  int could_not_decrypt = 0;
  int needpass = -1, pgp_keyblock = 0;
  int clearsign = 0, rv, rc;
  int c = 1; /* silence GCC warning */
  long bytes;
  LOFF_T last_pos, offset;
  char buf[HUGE_STRING];
  char outfile[_POSIX_PATH_MAX];
  char tmpfname[_POSIX_PATH_MAX];
  FILE *pgpout = NULL, *pgpin = NULL, *pgperr = NULL;
  FILE *tmpfp = NULL;
  pid_t thepid;

  short maybe_goodsig = 1;
  short have_any_sigs = 0;

  char *gpgcharset = NULL;
  char body_charset[STRING];
  mutt_get_body_charset (body_charset, sizeof (body_charset), m);

  rc = 0;	/* silence false compiler warning if (s->flags & MUTT_DISPLAY) */

  fseeko (s->fpin, m->offset, 0);
  last_pos = m->offset;
  
  for (bytes = m->length; bytes > 0;)
  {
    if (fgets (buf, sizeof (buf), s->fpin) == NULL)
      break;
    
    offset = ftello (s->fpin);
    bytes -= (offset - last_pos); /* don't rely on mutt_strlen(buf) */
    last_pos = offset;
    
    if (mutt_strncmp ("-----BEGIN PGP ", buf, 15) == 0)
    {
      clearsign = 0;

      if (mutt_strcmp ("MESSAGE-----\n", buf + 15) == 0)
        needpass = 1;
      else if (mutt_strcmp ("SIGNED MESSAGE-----\n", buf + 15) == 0)
      {
	clearsign = 1;
        needpass = 0;
      }
      else if (!mutt_strcmp ("PUBLIC KEY BLOCK-----\n", buf + 15))
      {
        needpass = 0;
        pgp_keyblock = 1;
      } 
      else
      {
	/* XXX - we may wish to recode here */
	if (s->prefix)
	  state_puts (s->prefix, s);
	state_puts (buf, s);
	continue;
      }

      have_any_sigs = have_any_sigs || (clearsign && (s->flags & MUTT_VERIFY));

      /* Copy PGP material to temporary file */
      mutt_mktemp (tmpfname, sizeof (tmpfname));
      if ((tmpfp = safe_fopen (tmpfname, "w+")) == NULL)
      {
	mutt_perror (tmpfname);
	return -1;
      }
      
      fputs (buf, tmpfp);
      while (bytes > 0 && fgets (buf, sizeof (buf) - 1, s->fpin) != NULL)
      {
	offset = ftello (s->fpin);
	bytes -= (offset - last_pos); /* don't rely on mutt_strlen(buf) */
	last_pos = offset;
	
	fputs (buf, tmpfp);

	if ((needpass && mutt_strcmp ("-----END PGP MESSAGE-----\n", buf) == 0) ||
	    (!needpass 
             && (mutt_strcmp ("-----END PGP SIGNATURE-----\n", buf) == 0
                 || mutt_strcmp ("-----END PGP PUBLIC KEY BLOCK-----\n",buf) == 0)))
	  break;
	/* remember optional Charset: armor header as defined by RfC4880 */
	if (mutt_strncmp ("Charset: ", buf, 9) == 0)
	{
	  size_t l = 0;
	  gpgcharset = safe_strdup (buf + 9);
	  if ((l = mutt_strlen (gpgcharset)) > 0 && gpgcharset[l-1] == '\n')
	    gpgcharset[l-1] = 0;
	  if (mutt_check_charset (gpgcharset, 0) < 0)
	    mutt_str_replace (&gpgcharset, "UTF-8");
	}
      }

      /* leave tmpfp open in case we still need it - but flush it! */
      fflush (tmpfp);

      /* Invoke PGP if needed */
      if (!clearsign || (s->flags & MUTT_VERIFY))
      {
	mutt_mktemp (outfile, sizeof (outfile));
	if ((pgpout = safe_fopen (outfile, "w+")) == NULL)
	{
	  mutt_perror (outfile);
	  return -1;
	}
	
	if ((thepid = pgp_invoke_decode (&pgpin, NULL, &pgperr, -1,
					 fileno (pgpout), -1, tmpfname,
					 needpass)) == -1)
	{
	  safe_fclose (&pgpout);
	  maybe_goodsig = 0;
	  pgpin = NULL;
	  pgperr = NULL;
	  state_attach_puts (_("[-- Error: unable to create PGP subprocess! --]\n"), s);
	}
	else /* PGP started successfully */
	{
	  if (needpass)
	  {
	    if (!pgp_valid_passphrase ()) pgp_void_passphrase();
            if (pgp_use_gpg_agent())
              *PgpPass = 0;
	    fprintf (pgpin, "%s\n", PgpPass);
	  }
	  
	  safe_fclose (&pgpin);

	  if (s->flags & MUTT_DISPLAY)
	  {
	    crypt_current_time (s, "PGP");
	    rc = pgp_copy_checksig (pgperr, s->fpout);
	  }
	  
	  safe_fclose (&pgperr);
	  rv = mutt_wait_filter (thepid);
	  
	  if (s->flags & MUTT_DISPLAY)
	  {
	    if (rc == 0) have_any_sigs = 1;
	    /*
	     * Sig is bad if
	     * gpg_good_sign-pattern did not match || pgp_decode_command returned not 0
	     * Sig _is_ correct if
	     *  gpg_good_sign="" && pgp_decode_command returned 0
	     */
	    if (rc == -1 || rv) maybe_goodsig = 0;
	    
	    state_attach_puts (_("[-- End of PGP output --]\n\n"), s);
	  }
	  if (pgp_use_gpg_agent())
	    mutt_need_hard_redraw ();
	}
	
        /* treat empty result as sign of failure */
	/* TODO: maybe on failure mutt should include the original undecoded text. */
	if (pgpout)
	{
	  rewind (pgpout);
	  c = fgetc (pgpout);
	  ungetc (c, pgpout);
	}
        if (!clearsign && (!pgpout || c == EOF))
	{
	  could_not_decrypt = 1;
	  pgp_void_passphrase ();
	}
	
	if (could_not_decrypt && !(s->flags & MUTT_DISPLAY))
	{
          mutt_error _("Could not decrypt PGP message");
	  mutt_sleep (1);
	  rc = -1;
	  goto out;
        }
      }
      
      /*
       * Now, copy cleartext to the screen.
       */

      if(s->flags & MUTT_DISPLAY)
      {
	if (needpass)
	  state_attach_puts (_("[-- BEGIN PGP MESSAGE --]\n\n"), s);
	else if (pgp_keyblock)
	  state_attach_puts (_("[-- BEGIN PGP PUBLIC KEY BLOCK --]\n"), s);
	else
	  state_attach_puts (_("[-- BEGIN PGP SIGNED MESSAGE --]\n\n"), s);
      }

      if (clearsign)
      {
	rewind (tmpfp);
	if (tmpfp) 
	  pgp_copy_clearsigned (tmpfp, s, body_charset);
      }
      else if (pgpout)
      {
	FGETCONV *fc;
	int c;
	char *expected_charset = gpgcharset && *gpgcharset ? gpgcharset : "utf-8";

	dprint(4,(debugfile,"pgp: recoding inline from [%s] to [%s]\n",
		  expected_charset, Charset));

	rewind (pgpout);
	state_set_prefix (s);
	fc = fgetconv_open (pgpout, expected_charset, Charset, MUTT_ICONV_HOOK_FROM);
	while ((c = fgetconv (fc)) != EOF)
	  state_prefix_putc (c, s);
	fgetconv_close (&fc);
      }

      /*
       * Multiple PGP blocks can exist, so these need to be closed and
       * unlinked inside the loop.
       */
      safe_fclose (&tmpfp);
      mutt_unlink (tmpfname);
      if (pgpout)
      {
	safe_fclose (&pgpout);
	mutt_unlink (outfile);
      }

      if (s->flags & MUTT_DISPLAY)
      {
	state_putc ('\n', s);
	if (needpass)
        {
	  state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
	  if (could_not_decrypt)
	    mutt_error _("Could not decrypt PGP message");
	  else
	    mutt_message _("PGP message successfully decrypted.");
        }
	else if (pgp_keyblock)
	  state_attach_puts (_("[-- END PGP PUBLIC KEY BLOCK --]\n"), s);
	else
	  state_attach_puts (_("[-- END PGP SIGNED MESSAGE --]\n"), s);
      }
    }
    else
    {
      /* A traditional PGP part may mix signed and unsigned content */
      /* XXX - we may wish to recode here */
      if (s->prefix)
	state_puts (s->prefix, s);
      state_puts (buf, s);
    }
  }

  rc = 0;

out:
  m->goodsig = (maybe_goodsig && have_any_sigs);

  if (tmpfp)
  {
    safe_fclose (&tmpfp);
    mutt_unlink (tmpfname);
  }
  if (pgpout)
  {
    safe_fclose (&pgpout);
    mutt_unlink (outfile);
  }

  FREE(&gpgcharset);

  if (needpass == -1)
  {
    state_attach_puts (_("[-- Error: could not find beginning of PGP message! --]\n\n"), s);
    return -1;
  }
  
  return rc;
}