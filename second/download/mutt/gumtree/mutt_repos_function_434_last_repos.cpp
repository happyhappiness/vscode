static BODY *smime_handle_entity (BODY *m, STATE *s, FILE *outFile)
{
  int len=0;
  int c;
  char buf[HUGE_STRING];
  char outfile[_POSIX_PATH_MAX], errfile[_POSIX_PATH_MAX];
  char tmpfname[_POSIX_PATH_MAX];
  char tmptmpfname[_POSIX_PATH_MAX];
  FILE *smimeout = NULL, *smimein=NULL, *smimeerr=NULL;
  FILE *tmpfp=NULL, *tmpfp_buffer=NULL, *fpout=NULL;
  struct stat info;
  BODY *p=NULL;
  pid_t thepid=-1;
  unsigned int type = mutt_is_application_smime (m);

  if (!(type & APPLICATION_SMIME)) return NULL;

  mutt_mktemp (outfile, sizeof (outfile));
  if ((smimeout = safe_fopen (outfile, "w+")) == NULL)
  {
    mutt_perror (outfile);
    return NULL;
  }
  
  mutt_mktemp (errfile, sizeof (errfile));
  if ((smimeerr = safe_fopen (errfile, "w+")) == NULL)
  {
    mutt_perror (errfile);
    safe_fclose (&smimeout); smimeout = NULL;
    return NULL;
  }
  mutt_unlink (errfile);

  
  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((tmpfp = safe_fopen (tmpfname, "w+")) == NULL)
  {
    mutt_perror (tmpfname);
    safe_fclose (&smimeout); smimeout = NULL;
    safe_fclose (&smimeerr); smimeerr = NULL;
    return NULL;
  }

  fseeko (s->fpin, m->offset, 0);

  mutt_copy_bytes (s->fpin, tmpfp,  m->length);

  fflush (tmpfp);
  safe_fclose (&tmpfp);

  if ((type & ENCRYPT) &&
      (thepid = smime_invoke_decrypt (&smimein, NULL, NULL, -1,
				      fileno (smimeout),  fileno (smimeerr), tmpfname)) == -1)
  {
    safe_fclose (&smimeout); smimeout = NULL;
    mutt_unlink (tmpfname);
    if (s->flags & MUTT_DISPLAY)
      state_attach_puts (_("[-- Error: unable to create OpenSSL subprocess! --]\n"), s);
    return NULL;
  }
  else if ((type & SIGNOPAQUE) &&
	   (thepid = smime_invoke_verify (&smimein, NULL, NULL, -1,
					  fileno (smimeout), fileno (smimeerr), NULL,
					  tmpfname, SIGNOPAQUE)) == -1)
  {
    safe_fclose (&smimeout); smimeout = NULL;
    mutt_unlink (tmpfname);
    if (s->flags & MUTT_DISPLAY)
      state_attach_puts (_("[-- Error: unable to create OpenSSL subprocess! --]\n"), s);
    return NULL;
  }

  
  if (type & ENCRYPT)
  {
    if (!smime_valid_passphrase ())
      smime_void_passphrase ();
    fputs (SmimePass, smimein);
    fputc ('\n', smimein);
  }

  safe_fclose (&smimein);
	
  mutt_wait_filter (thepid);
  mutt_unlink (tmpfname);
  

  if (s->flags & MUTT_DISPLAY)
  {
    fflush (smimeerr);
    rewind (smimeerr);
    
    if ((c = fgetc (smimeerr)) != EOF)
    {
      ungetc (c, smimeerr);
      
      crypt_current_time (s, "OpenSSL");
      mutt_copy_stream (smimeerr, s->fpout);
      state_attach_puts (_("[-- End of OpenSSL output --]\n\n"), s);
    }
    
    if (type & ENCRYPT)
      state_attach_puts (_("[-- The following data is S/MIME"
                           " encrypted --]\n"), s);
    else
      state_attach_puts (_("[-- The following data is S/MIME signed --]\n"), s);
  }

  if (smimeout)
  {
    fflush (smimeout);
    rewind (smimeout);
    
    if (outFile) fpout = outFile;
    else
    {
      mutt_mktemp (tmptmpfname, sizeof (tmptmpfname));
      if ((fpout = safe_fopen (tmptmpfname, "w+")) == NULL)
      {
	mutt_perror(tmptmpfname);
	safe_fclose (&smimeout); smimeout = NULL;
	return NULL;
      }
    }
    while (fgets (buf, sizeof (buf) - 1, smimeout) != NULL)
    {
      len = mutt_strlen (buf);
      if (len > 1 && buf[len - 2] == '\r')
      {
	buf[len-2] = '\n';
	buf[len-1] = '\0';
      }
      fputs (buf, fpout);
    }
    fflush (fpout);
    rewind (fpout); 


    if ((p = mutt_read_mime_header (fpout, 0)) != NULL)
    {
      fstat (fileno (fpout), &info);
      p->length = info.st_size - p->offset;
	  
      mutt_parse_part (fpout, p);
      if (s->fpout)
      {
	rewind (fpout);
	tmpfp_buffer = s->fpin;
	s->fpin = fpout;
	mutt_body_handler (p, s);
	s->fpin = tmpfp_buffer;
      }
      
    }
    safe_fclose (&smimeout);
    smimeout = NULL;
    mutt_unlink (outfile);

    if (!outFile)
    {
      safe_fclose (&fpout);
      mutt_unlink (tmptmpfname);
    }
    fpout = NULL;
  }

  if (s->flags & MUTT_DISPLAY)
  {
    if (type & ENCRYPT)
      state_attach_puts (_("\n[-- End of S/MIME encrypted data. --]\n"), s);
    else
      state_attach_puts (_("\n[-- End of S/MIME signed data. --]\n"), s);
  }

  if (type & SIGNOPAQUE)
  {
    char *line = NULL;
    int lineno = 0;
    size_t linelen;
    
    rewind (smimeerr);
    
    line = mutt_read_line (line, &linelen, smimeerr, &lineno, 0);
    if (linelen && !ascii_strcasecmp (line, "verification successful"))
      m->goodsig = 1;
    FREE (&line);
  }
  else 
  {
    m->goodsig = p->goodsig;
    m->badsig  = p->badsig;
  }
  safe_fclose (&smimeerr);

  return (p);
}