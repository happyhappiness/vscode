int pgp_verify_one (BODY *sigbdy, STATE *s, const char *tempfile)
{
  char sigfile[_POSIX_PATH_MAX], pgperrfile[_POSIX_PATH_MAX];
  FILE *fp, *pgpout, *pgperr;
  pid_t thepid;
  int badsig = -1;
  int rv;
  
  snprintf (sigfile, sizeof (sigfile), "%s.asc", tempfile);
  
  if(!(fp = safe_fopen (sigfile, "w")))
  {
    mutt_perror(sigfile);
    return -1;
  }
	
  fseeko (s->fpin, sigbdy->offset, 0);
  mutt_copy_bytes (s->fpin, fp, sigbdy->length);
  safe_fclose (&fp);
  
  mutt_mktemp (pgperrfile, sizeof (pgperrfile));
  if(!(pgperr = safe_fopen(pgperrfile, "w+")))
  {
    mutt_perror(pgperrfile);
    unlink(sigfile);
    return -1;
  }
  
  crypt_current_time (s, "PGP");
  
  if((thepid = pgp_invoke_verify (NULL, &pgpout, NULL, 
				   -1, -1, fileno(pgperr),
				   tempfile, sigfile)) != -1)
  {
    if (pgp_copy_checksig (pgpout, s->fpout) >= 0)
      badsig = 0;
    
    
    safe_fclose (&pgpout);
    fflush (pgperr);
    rewind (pgperr);
    
    if (pgp_copy_checksig  (pgperr, s->fpout) >= 0)
      badsig = 0;

    if ((rv = mutt_wait_filter (thepid)))
      badsig = -1;
    
     dprint (1, (debugfile, "pgp_verify_one: mutt_wait_filter returned %d.\n", rv));
  }

  safe_fclose (&pgperr);

  state_attach_puts (_("[-- End of PGP output --]\n\n"), s);

  mutt_unlink (sigfile);
  mutt_unlink (pgperrfile);

  dprint (1, (debugfile, "pgp_verify_one: returning %d.\n", badsig));
  
  return badsig;
}