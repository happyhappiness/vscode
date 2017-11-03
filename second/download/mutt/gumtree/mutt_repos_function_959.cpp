static int tls_check_stored_hostname (const gnutls_datum_t *cert,
                                      const char *hostname)
{
  char buf[80];
  FILE *fp;
  char *linestr = NULL;
  size_t linestrsize;
  int linenum = 0;
  regex_t preg;
  regmatch_t pmatch[3];

  /* try checking against names stored in stored certs file */
  if ((fp = fopen (SslCertFile, "r")))
  {
    if (REGCOMP(&preg, "^#H ([a-zA-Z0-9_\\.-]+) ([0-9A-F]{4}( [0-9A-F]{4}){7})[ \t]*$",
                REG_ICASE) != 0)
    {
       return 0;
    }

    buf[0] = '\0';
    tls_fingerprint (GNUTLS_DIG_MD5, buf, sizeof (buf), cert);
    while ((linestr = mutt_read_line(linestr, &linestrsize, fp, &linenum, 0)) != NULL)
    {
      if(linestr[0] == '#' && linestr[1] == 'H')
      {
        if (regexec(&preg, linestr, 3, pmatch, 0) == 0)
        {
          linestr[pmatch[1].rm_eo] = '\0';
          linestr[pmatch[2].rm_eo] = '\0';
          if (strcmp(linestr + pmatch[1].rm_so, hostname) == 0 &&
              strcmp(linestr + pmatch[2].rm_so, buf) == 0)
          {
            regfree(&preg);
            FREE(&linestr);
            safe_fclose (&fp);
            return 1;
          }
        }
      }
    }

    regfree(&preg);
    safe_fclose (&fp);
  }

  /* not found a matching name */
  return 0;
}