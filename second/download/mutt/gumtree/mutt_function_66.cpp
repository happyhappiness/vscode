void pgp_application_pgp_handler (BODY *m, STATE *s)
{
  int needpass = -1, pgp_keyblock = 0;
  int clearsign = 0, rv, rc;
  long start_pos = 0;
  long bytes, last_pos, offset;
  char buf[HUGE_STRING];
  char outfile[_POSIX_PATH_MAX];
  char tmpfname[_POSIX_PATH_MAX];
  FILE *pgpout = NULL, *pgpin = NULL, *pgperr = NULL;
  FILE *tmpfp;
  pid_t thepid;

  short maybe_goodsig = 1;
  short have_any_sigs = 0;
  
  fseek (s->fpin, m->offset, 0);
  last_pos = m->offset;
  
  for (bytes = m->length; bytes > 0;)
  {
    if (fgets (buf, sizeof (buf) - 1, s->fpin) == NULL)
      break;
    
    offset = ftell (s->fpin);
    bytes -= (offset - last_pos); /* don't rely on mutt_strlen(buf) */
    last_pos = offset;
    
    if (mutt_strncmp ("-----BEGIN PGP ", buf, 15) == 0)
    {
      clearsign = 0;
      start_pos = last_pos;

      if (mutt_strcmp ("MESSAGE-----\n", buf + 15) == 0)
        needpass = 1;
      else if (mutt_strcmp ("SIGNED MESSAGE-----\n", buf + 15) == 0)
      {
	clearsign = 1;
        needpass = 0;
      }
      else if (!option (OPTDONTHANDLEPGPKEYS) &&
	       mutt_strcmp ("PUBLIC KEY BLOCK-----\n", buf + 15) == 0) 
      {
        needpass = 0;
        pgp_keyblock =1;
      } 
      else
      {
	if (s->prefix)
	  state_puts (s->prefix, s);
	state_puts (buf, s);
	continue;
      }

      have_any_sigs = have_any_sigs || (clearsign && (s->flags & M_VERIFY));
      
      if(!clearsign || s->flags & M_VERIFY)
      {

	/* invoke PGP */
	
	mutt_mktemp (outfile);
	if ((pgpout = safe_fopen (outfile, "w+")) == NULL)
	{
	  mutt_perror (outfile);
	  return;
	}
	
	mutt_mktemp (tmpfname);
	if ((tmpfp = safe_fopen (tmpfname, "w+")) == NULL)
	{
	  mutt_perror (tmpfname);
	  safe_fclose (&pgpout); 
	  return;
	}
	
	fputs (buf, tmpfp);
	while (bytes > 0 && fgets (buf, sizeof (buf) - 1, s->fpin) != NULL)
	{
	  offset = ftell (s->fpin);
	  bytes -= (offset - last_pos); /* don't rely on mutt_strlen(buf) */
	  last_pos = offset;
	  
	  fputs (buf, tmpfp);
	  if ((needpass && mutt_strcmp ("-----END PGP MESSAGE-----\n", buf) == 0) ||
	      (!needpass 
             && (mutt_strcmp ("-----END PGP SIGNATURE-----\n", buf) == 0
                 || mutt_strcmp ("-----END PGP PUBLIC KEY BLOCK-----\n",buf) == 0)))
	    break;
	}

	safe_fclose (&tmpfp);
	
	if ((thepid = pgp_invoke_decode (&pgpin, NULL,
					  &pgperr, -1,
					  fileno (pgpout), 
					  -1, tmpfname, 
					  needpass)) == -1)
	{
	  safe_fclose (&pgpout);
	  mutt_unlink (tmpfname);

	  maybe_goodsig = 0;

	  pgpin = NULL;
	  pgperr = NULL;
	  
	  state_attach_puts (_("[-- Error: unable to create PGP subprocess! --]\n"), s);
	}
	else
	{
	  if (needpass)
	  {
	    if (!pgp_valid_passphrase ())
	      pgp_void_passphrase ();
	    fputs (PgpPass, pgpin);
	    fputc ('\n', pgpin);
	  }
	  
	  safe_fclose (&pgpin);
	  
	  if (s->flags & M_DISPLAY)
	    pgp_current_time (s);
	  
	  rv = mutt_wait_filter (thepid);
	  
	  mutt_unlink (tmpfname);
	
	  if (s->flags & M_DISPLAY)
	  {
	    rc = pgp_copy_checksig (pgperr, s->fpout);
	    
	    if (rc == 0)
	      have_any_sigs = 1;
	    if (rc || rv)
	      maybe_goodsig = 0;
	  }
	  
	  safe_fclose (&pgperr);

	  if (s->flags & M_DISPLAY)
	  {
	    state_putc ('\n', s);
	    state_attach_puts (_("[-- End of PGP output --]\n\n"), s);
	  }
	}
      }
    
      if(s->flags & M_DISPLAY)
      {
	if (needpass)
	  state_attach_puts (_("[-- BEGIN PGP MESSAGE --]\n\n"), s);
	else if (pgp_keyblock)
	  state_attach_puts (_("[-- BEGIN PGP PUBLIC KEY BLOCK --]\n"), s);
	else
	  state_attach_puts (_("[-- BEGIN PGP SIGNED MESSAGE --]\n\n"), s);
      }

      /* Use PGP's output if there was no clearsig signature. */
      
      if(!clearsign && pgpout)
      {
	fflush (pgpout);
	rewind (pgpout);
	while (fgets (buf, sizeof (buf) - 1, pgpout) != NULL)
	{
	  if (s->prefix)
	    state_puts (s->prefix, s);
	  state_puts (buf, s);
	}
      }

      /* Close the temporary files iff they were created. 
       * The condition used to be !clearsign || s->flags & M_VERIFY,
       * but gcc would complain then.
       */
      
      if(pgpout)
      {
	safe_fclose (&pgpout);
	mutt_unlink (outfile);
      }

      /* decode clearsign stuff */
      
      if (clearsign)
      {
	fseek (s->fpin, start_pos, SEEK_SET);
	bytes   += (last_pos - start_pos);
	bytes    = pgp_copy_clearsigned (s, bytes);
	last_pos = ftell (s->fpin);
      }

      if (s->flags & M_DISPLAY)
      {
	state_putc ('\n', s);
	if (needpass)
	  state_attach_puts (_("[-- END PGP MESSAGE --]\n"), s);
	else if (pgp_keyblock)
	  state_attach_puts (_("[-- END PGP PUBLIC KEY BLOCK --]\n"), s);
	else
	  state_attach_puts (_("[-- END PGP SIGNED MESSAGE --]\n"), s);
      }
    }
    else
    {
      if (s->prefix)
	state_puts (s->prefix, s);
      state_puts (buf, s);
    }
  }

  m->goodsig = (maybe_goodsig && have_any_sigs);

  if (needpass == -1)
  {
    state_attach_puts (_("[-- Error: could not find beginning of PGP message! --]\n\n"), s);
    return;
  }
}