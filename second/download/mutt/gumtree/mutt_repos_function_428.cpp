int smime_verify_one (BODY *sigbdy, STATE *s, const char *tempfile)
{
  char signedfile[_POSIX_PATH_MAX], smimeerrfile[_POSIX_PATH_MAX];
  FILE *fp=NULL, *smimeout=NULL, *smimeerr=NULL;
  pid_t thepid;
  int badsig = -1;

  LOFF_T tmpoffset = 0;
  size_t tmplength = 0;
  int origType = sigbdy->type;
  char *savePrefix = NULL;


  snprintf (signedfile, sizeof (signedfile), "%s.sig", tempfile);
  
  /* decode to a tempfile, saving the original destination */
  fp = s->fpout;
  if ((s->fpout = safe_fopen (signedfile, "w")) == NULL)
  {
    mutt_perror (signedfile);
    return -1;
  }
  /* decoding the attachment changes the size and offset, so save a copy
   * of the "real" values now, and restore them after processing
   */
  tmplength = sigbdy->length;
  tmpoffset = sigbdy->offset;

  /* if we are decoding binary bodies, we don't want to prefix each
   * line with the prefix or else the data will get corrupted.
   */
  savePrefix = s->prefix;
  s->prefix = NULL;

  mutt_decode_attachment (sigbdy, s);

  sigbdy->length = ftello (s->fpout);
  sigbdy->offset = 0;
  safe_fclose (&s->fpout);

  /* restore final destination and substitute the tempfile for input */
  s->fpout = fp;
  fp = s->fpin;
  s->fpin = fopen (signedfile, "r");

  /* restore the prefix */
  s->prefix = savePrefix;
  
  sigbdy->type = origType;

  
  mutt_mktemp (smimeerrfile, sizeof (smimeerrfile));
  if (!(smimeerr = safe_fopen (smimeerrfile, "w+")))
  {
    mutt_perror (smimeerrfile);
    mutt_unlink (signedfile);
    return -1;
  }
  
  crypt_current_time (s, "OpenSSL");
  
  if ((thepid = smime_invoke_verify (NULL, &smimeout, NULL, 
				   -1, -1, fileno (smimeerr),
				   tempfile, signedfile, 0)) != -1)
  {
    fflush (smimeout);
    safe_fclose (&smimeout);
      
    if (mutt_wait_filter (thepid))
      badsig = -1;
    else
    {
      char *line = NULL;
      int lineno = 0;
      size_t linelen;
      
      fflush (smimeerr);
      rewind (smimeerr);
      
      line = mutt_read_line (line, &linelen, smimeerr, &lineno, 0);
      if (linelen && !ascii_strcasecmp (line, "verification successful"))
	badsig = 0;

      FREE (&line);
    }
  }
  
  fflush (smimeerr);
  rewind (smimeerr);
  mutt_copy_stream (smimeerr, s->fpout);
  safe_fclose (&smimeerr);
    
  state_attach_puts (_("[-- End of OpenSSL output --]\n\n"), s);
  
  mutt_unlink (signedfile);
  mutt_unlink (smimeerrfile);

  sigbdy->length = tmplength;
  sigbdy->offset = tmpoffset;
  
  /* restore the original source stream */
  safe_fclose (&s->fpin);
  s->fpin = fp;
  

  return badsig;
}