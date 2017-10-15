    if (buf[0] == '-' && buf[1] == ' ')
      state_puts (buf + 2, s);
    else
      state_puts (buf, s);
  }
  
  if (!have_sig)
    return bytes;
    
  for (complete = 1;
       bytes > 0 && fgets (buf, sizeof (buf), s->fpin) != NULL;
       complete = strchr (buf, '\n') != NULL)
  {
    offset   = ftell (s->fpin);
    bytes   -= (offset - last_pos);
    last_pos = offset;
    
    if (mutt_strcmp (buf, "-----END PGP SIGNATURE-----\n") == 0)
      break;
  }
  
  return bytes;
}


/* Support for the Application/PGP Content Type. */

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

static int pgp_check_traditional_one_body (FILE *fp, BODY *b, int tagged_only)
{
  char tempfile[_POSIX_PATH_MAX];
  char buf[HUGE_STRING];
  FILE *tfp;
  
  short sgn = 0;
  short enc = 0;
  
  if (b->type != TYPETEXT)
    return 0;

  if (tagged_only && !b->tagged)
    return 0;
  
  mutt_mktemp (tempfile);
  if (mutt_decode_save_attachment (fp, b, tempfile, 0, 0) != 0)
  {
    unlink (tempfile);
    return 0;
  }
  
  if ((tfp = fopen (tempfile, "r")) == NULL)
  {
    unlink (tempfile);
    return 0;
  }
    
  while (fgets (buf, sizeof (buf), tfp))
  {
    if (mutt_strncmp ("-----BEGIN PGP ", buf, 15) == 0)
    {
      if (mutt_strcmp ("MESSAGE-----\n", buf + 15) == 0)
	enc = 1;
      else if (mutt_strcmp ("SIGNED MESSAGE-----\n", buf + 15) == 0)
	sgn = 1;
    }
  }
  
  safe_fclose (&tfp);
  unlink (tempfile);

  if (!enc && !sgn)
    return 0;

  /* fix the content type */
  
  b->type = TYPEAPPLICATION;
  mutt_str_replace (&b->subtype, "pgp");
  
  mutt_set_parameter ("format", "text", &b->parameter);
  mutt_set_parameter ("x-action", enc ? "encrypt" : "sign", &b->parameter);
  
  return 1;
}

int pgp_check_traditional (FILE *fp, BODY *b, int tagged_only)
{
  int rv = 0;
  for (; b; b = b->next)
  {
    if (is_multipart (b))
      rv = pgp_check_traditional (fp, b->parts, tagged_only) || rv;
    else if (b->type == TYPETEXT)
      rv = pgp_check_traditional_one_body (fp, b, tagged_only) || rv;
  }

  return rv;
}

int mutt_is_multipart_signed (BODY *b)
{
  char *p;

  if (!b || b->type != TYPEMULTIPART ||
      !b->subtype || ascii_strcasecmp (b->subtype, "signed") ||
      !(p = mutt_get_parameter ("protocol", b->parameter)) ||
      (ascii_strcasecmp (p, "application/pgp-signature")
      && ascii_strcasecmp (p, "multipart/mixed")))
    return 0;

  return PGPSIGN;
}
   
     
int mutt_is_multipart_encrypted (BODY *b)
{
  char *p;
  
  if (!b || b->type != TYPEMULTIPART ||
      !b->subtype || ascii_strcasecmp (b->subtype, "encrypted") ||
      !(p = mutt_get_parameter ("protocol", b->parameter)) ||
      ascii_strcasecmp (p, "application/pgp-encrypted"))
    return 0;
  
  return PGPENCRYPT;
}

int mutt_is_application_pgp (BODY *m)
{
  int t = 0;
  char *p;
  
  if (m->type == TYPEAPPLICATION)
  {
    if (!ascii_strcasecmp (m->subtype, "pgp") || !ascii_strcasecmp (m->subtype, "x-pgp-message"))
    {
      if ((p = mutt_get_parameter ("x-action", m->parameter))
	  && (!ascii_strcasecmp (p, "sign") || !ascii_strcasecmp (p, "signclear")))
	t |= PGPSIGN;

      if ((p = mutt_get_parameter ("format", m->parameter)) && 
	  !ascii_strcasecmp (p, "keys-only"))
	t |= PGPKEY;

      if(!t) t |= PGPENCRYPT;  /* not necessarily correct, but... */
    }

    if (!ascii_strcasecmp (m->subtype, "pgp-signed"))
      t |= PGPSIGN;

    if (!ascii_strcasecmp (m->subtype, "pgp-keys"))
      t |= PGPKEY;
  }
  return t;
}

int pgp_query (BODY *m)
{
  int t = 0;

  t |= mutt_is_application_pgp (m);

  if ((t & (PGPSIGN|PGPENCRYPT)) && m->goodsig)
    t |= PGPGOODSIGN|PGPSIGN;
  else if (m->type == TYPEMULTIPART)
  {
    if (mutt_is_multipart_signed(m))
      t |= PGPSIGN;
    else if (mutt_is_multipart_encrypted(m))
      t |= PGPENCRYPT;

    if (m->goodsig && 
	(mutt_is_multipart_signed (m) || mutt_is_multipart_encrypted (m)))
      t |= PGPGOODSIGN;
  }
  
  if (m->type == TYPEMULTIPART || m->type == TYPEMESSAGE)
  {
    BODY *p;
 
    for (p = m->parts; p; p = p->next)
      t |= pgp_query(p) & ~PGPGOODSIGN;
  }

  return t;
}

static void pgp_fetch_signatures (BODY ***signatures, BODY *a, int *n)
{
  for (; a; a = a->next)
  {
    if(a->type == TYPEMULTIPART)
      pgp_fetch_signatures (signatures, a->parts, n);
    else
    {
      if((*n % 5) == 0)
	safe_realloc((void **) signatures, (*n + 6) * sizeof(BODY **));

      (*signatures)[(*n)++] = a;
    }
  }
}

static int pgp_write_signed(BODY *a, STATE *s, const char *tempfile)
{
  FILE *fp;
  int c;
  short hadcr;
  size_t bytes;

  if(!(fp = safe_fopen (tempfile, "w")))
  {
    mutt_perror(tempfile);
    return -1;
  }
      
  fseek (s->fpin, a->hdr_offset, 0);
  bytes = a->length + a->offset - a->hdr_offset;
  hadcr = 0;
  while (bytes > 0)
  {
    if((c = fgetc(s->fpin)) == EOF)
      break;
    
    bytes--;
    
    if(c == '\r')
      hadcr = 1;
    else 
    {
      if(c == '\n' && !hadcr)
	fputc('\r', fp);
      
      hadcr = 0;
    }
    
    fputc(c, fp);
    
  }
  fclose (fp);

  return 0;
}


static int pgp_verify_one (BODY *sigbdy, STATE *s, const char *tempfile)
{
  char sigfile[_POSIX_PATH_MAX], pgperrfile[_POSIX_PATH_MAX];
  FILE *fp, *pgpout, *pgperr;
  pid_t thepid;
  int badsig = -1;
  int rv;
