  if (PgpGoodSign.pattern)
  {
    char *line = NULL;
    int lineno = 0;
    size_t linelen;
    
    while ((line = mutt_read_line (line, &linelen, fpin, &lineno)) != NULL)
    {
      if (regexec (PgpGoodSign.rx, line, 0, NULL, 0) == 0)
      {
	dprint (2, (debugfile, "pgp_copy_checksig: \"%s\" matches regexp.\n",
		    line));
	rv = 0;
      }
      else
	dprint (2, (debugfile, "pgp_copy_checksig: \"%s\" doesn't match regexp.\n",
		    line));
      
      fputs (line, fpout);
      fputc ('\n', fpout);
    }
    safe_free ((void **) &line);
  }
  else
  {
    dprint (2, (debugfile, "pgp_copy_checksig: No pattern.\n"));
    mutt_copy_stream (fpin, fpout);
    rv = 1;
