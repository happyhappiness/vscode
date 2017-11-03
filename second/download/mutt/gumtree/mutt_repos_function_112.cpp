int pop_authenticate (POP_DATA* pop_data)
{
  ACCOUNT *acct = &pop_data->conn->account;
  const pop_auth_t* authenticator;
  char* methods;
  char* comma;
  char* method;
  int attempts = 0;
  int ret = POP_A_UNAVAIL;

  if (mutt_account_getuser (acct) || !acct->user[0] ||
      mutt_account_getpass (acct) || !acct->pass[0])
    return -3;

  if (PopAuthenticators && *PopAuthenticators)
  {
    /* Try user-specified list of authentication methods */
    methods = safe_strdup (PopAuthenticators);
    method = methods;

    while (method)
    {
      comma = strchr (method, ':');
      if (comma)
	*comma++ = '\0';
      dprint (2, (debugfile, "pop_authenticate: Trying method %s\n", method));
      authenticator = pop_authenticators;

      while (authenticator->authenticate)
      {
	if (!authenticator->method ||
	    !ascii_strcasecmp (authenticator->method, method))
	{
	  ret = authenticator->authenticate (pop_data, method);
	  if (ret == POP_A_SOCKET)
	    switch (pop_connect (pop_data))
	    {
	      case 0:
	      {
		ret = authenticator->authenticate (pop_data, method);
		break;
	      }
	      case -2:
		ret = POP_A_FAILURE;
	    }

	  if (ret != POP_A_UNAVAIL)
	    attempts++;
	  if (ret == POP_A_SUCCESS || ret == POP_A_SOCKET ||
	      (ret == POP_A_FAILURE && !option (OPTPOPAUTHTRYALL)))
	  {
	    comma = NULL;
	    break;
	  }
	}
	authenticator++;
      }

      method = comma;
    }

    FREE (&methods);
  }
  else
  {
    /* Fall back to default: any authenticator */
    dprint (2, (debugfile, "pop_authenticate: Using any available method.\n"));
    authenticator = pop_authenticators;

    while (authenticator->authenticate)
    {
      ret = authenticator->authenticate (pop_data, authenticator->method);
      if (ret == POP_A_SOCKET)
	switch (pop_connect (pop_data))
	{
	  case 0:
	  {
	    ret = authenticator->authenticate (pop_data, authenticator->method);
	    break;
	  }
	  case -2:
	    ret = POP_A_FAILURE;
	}

      if (ret != POP_A_UNAVAIL)
	attempts++;
      if (ret == POP_A_SUCCESS || ret == POP_A_SOCKET ||
	  (ret == POP_A_FAILURE && !option (OPTPOPAUTHTRYALL)))
	break;

      authenticator++;
    }
  }

  switch (ret)
  {
    case POP_A_SUCCESS:
      return 0;
    case POP_A_SOCKET:
      return -1;
    case POP_A_UNAVAIL:
      if (!attempts)
	mutt_error (_("No authenticators available"));
  }

  return -2;
}