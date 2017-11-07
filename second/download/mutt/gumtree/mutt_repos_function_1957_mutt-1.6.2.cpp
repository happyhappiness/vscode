int imap_authenticate (IMAP_DATA* idata)
{
  const imap_auth_t* authenticator;
  char* methods;
  char* method;
  char* delim;
  int r = -1;

  if (ImapAuthenticators && *ImapAuthenticators)
  {
    /* Try user-specified list of authentication methods */
    methods = safe_strdup (ImapAuthenticators);

    for (method = methods; method; method = delim)
    {
      delim = strchr (method, ':');
      if (delim)
	*delim++ = '\0';
      if (! method[0])
	continue;
      
      dprint (2, (debugfile, "imap_authenticate: Trying method %s\n", method));
      authenticator = imap_authenticators;

      while (authenticator->authenticate)
      {
	if (!authenticator->method ||
	    !ascii_strcasecmp (authenticator->method, method))
	  if ((r = authenticator->authenticate (idata, method)) !=
	      IMAP_AUTH_UNAVAIL)
	  {
	    FREE (&methods);
	    return r;
	  }
	
	authenticator++;
      }
    }

    FREE (&methods);
  }
  else
  {
    /* Fall back to default: any authenticator */
    dprint (2, (debugfile, "imap_authenticate: Using any available method.\n"));
    authenticator = imap_authenticators;

    while (authenticator->authenticate)
    {
      if ((r = authenticator->authenticate (idata, NULL)) != IMAP_AUTH_UNAVAIL)
	return r;
      authenticator++;
    }
  }

  if (r == IMAP_AUTH_UNAVAIL)
  {
    mutt_error (_("No authenticators available"));
    mutt_sleep (1);
  }
  
  return r;
}