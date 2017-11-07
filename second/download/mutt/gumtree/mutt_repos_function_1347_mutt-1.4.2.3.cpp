static int browse_get_namespace (IMAP_DATA* idata, char* nsbuf, int nsblen,
  IMAP_NAMESPACE_INFO* nsi, int nsilen, int* nns)
{
  char *s;
  int n;
  char ns[LONG_STRING];
  char delim = '/';
  int type;
  int nsbused = 0;
  int rc;

  *nns = 0;
  nsbuf[nsblen-1] = '\0';

  imap_cmd_start (idata, "NAMESPACE");
  
  do 
  {
    if ((rc = imap_cmd_step (idata)) != IMAP_CMD_CONTINUE)
      break;

    s = imap_next_word (idata->cmd.buf);
    if (ascii_strncasecmp ("NAMESPACE", s, 9) == 0)
    {
      /* There are three sections to the response, User, Other, Shared,
       * and maybe more by extension */
      for (type = IMAP_NS_PERSONAL; *s; type++)
      {
	s = imap_next_word (s);
	if (*s && ascii_strncasecmp (s, "NIL", 3))
	{
	  s++;
	  while (*s && *s != ')')
	  {
	    s++; /* skip ( */
	    /* copy namespace */
	    n = 0;
	    delim = '\0';

	    if (*s == '\"')
	    {
	      s++;
	      while (*s && *s != '\"' && n < sizeof (ns) - 1) 
	      {
		if (*s == '\\')
		  s++;
		ns[n++] = *s;
		s++;
	      }
	      if (*s)
		s++;
	    }
	    else
	      while (*s && !ISSPACE (*s) && n < sizeof (ns) - 1)
	      {
		ns[n++] = *s;
		s++;
	      }
	    ns[n] = '\0';
	    if (n == sizeof (ns) - 1)
	      dprint (1, (debugfile, "browse_get_namespace: too long: [%s]\n", ns));
	    /* delim? */
	    s = imap_next_word (s);
	    /* delimiter is meaningless if namespace is "". Why does
	     * Cyrus provide one?! */
	    if (n && *s && *s == '\"')
	    {
	      if (s[1] && s[2] == '\"')
		delim = s[1];
	      else if (s[1] && s[1] == '\\' && s[2] && s[3] == '\"')
		delim = s[2];
	    }
	    /* skip "" namespaces, they are already listed at the root */
	    if ((ns[0] != '\0') && (nsbused < nsblen) && (*nns < nsilen))
	    {
	      dprint (3, (debugfile, "browse_get_namespace: adding %s\n", ns));
	      nsi->type = type;
	      /* Cyrus doesn't append the delimiter to the namespace,
	       * but UW-IMAP does. We'll strip it here and add it back
	       * as if it were a normal directory, from the browser */
	      if (n && (ns[n-1] == delim))
		ns[--n] = '\0';
	      strncpy (nsbuf+nsbused,ns,nsblen-nsbused-1);
	      nsi->prefix = nsbuf+nsbused;
	      nsbused += n+1;
	      nsi->delim = delim;
	      nsi++;
	      (*nns)++;
	    }
	    while (*s && *s != ')') 
	      s++;
	    if (*s)
	      s++;
	  }
	}
      }
    }
  }
  while (rc == IMAP_CMD_CONTINUE);

  if (rc != IMAP_CMD_OK)
    return -1;

  return 0;
}