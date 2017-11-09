int mutt_sasl_client_new (CONNECTION* conn, sasl_conn_t** saslconn)
{
  sasl_security_properties_t secprops;
  struct sockaddr_storage local, remote;
  socklen_t size;
  char iplocalport[IP_PORT_BUFLEN], ipremoteport[IP_PORT_BUFLEN];
  char* plp = NULL;
  char* prp = NULL;
  const char* service;
  int rc;

  if (mutt_sasl_start () != SASL_OK)
    return -1;

  switch (conn->account.type)
  {
    case MUTT_ACCT_TYPE_IMAP:
      service = "imap";
      break;
    case MUTT_ACCT_TYPE_POP:
      service = "pop";
      break;
    case MUTT_ACCT_TYPE_SMTP:
      service = "smtp";
      break;
    default:
      mutt_error (_("Unknown SASL profile"));
      return -1;
  }

  size = sizeof (local);
  if (!getsockname (conn->fd, (struct sockaddr *)&local, &size)) {
    if (iptostring((struct sockaddr *)&local, size, iplocalport,
                   IP_PORT_BUFLEN) == SASL_OK)
      plp = iplocalport;
    else
      dprint (2, (debugfile, "SASL failed to parse local IP address\n"));
  }
  else
    dprint (2, (debugfile, "SASL failed to get local IP address\n"));
  
  size = sizeof (remote);
  if (!getpeername (conn->fd, (struct sockaddr *)&remote, &size)){
    if (iptostring((struct sockaddr *)&remote, size, ipremoteport,
                   IP_PORT_BUFLEN) == SASL_OK)
      prp = ipremoteport;
    else
      dprint (2, (debugfile, "SASL failed to parse remote IP address\n"));
  }
  else
    dprint (2, (debugfile, "SASL failed to get remote IP address\n"));

  dprint (2, (debugfile, "SASL local ip: %s, remote ip:%s\n", NONULL(plp),
	      NONULL(prp)));
  
  rc = sasl_client_new (service, conn->account.host, plp, prp,
    mutt_sasl_get_callbacks (&conn->account), 0, saslconn);

  if (rc != SASL_OK)
  {
    mutt_error (_("Error allocating SASL connection"));
    mutt_sleep (2);
    return -1;
  }

  memset (&secprops, 0, sizeof (secprops));
  /* Work around a casting bug in the SASL krb4 module */
  secprops.max_ssf = 0x7fff;
  secprops.maxbufsize = MUTT_SASL_MAXBUF;
  if (sasl_setprop (*saslconn, SASL_SEC_PROPS, &secprops) != SASL_OK)
  {
    mutt_error (_("Error setting SASL security properties"));
    return -1;
  }

  if (conn->ssf)
  {
    /* I'm not sure this actually has an effect, at least with SASLv2 */
    dprint (2, (debugfile, "External SSF: %d\n", conn->ssf));
    if (sasl_setprop (*saslconn, SASL_SSF_EXTERNAL, &(conn->ssf)) != SASL_OK)
    {
      mutt_error (_("Error setting SASL external security strength"));
      return -1;
    }
  }
  if (conn->account.user[0])
  {
    dprint (2, (debugfile, "External authentication name: %s\n", conn->account.user));
    if (sasl_setprop (*saslconn, SASL_AUTH_EXTERNAL, conn->account.user) != SASL_OK)
    {
      mutt_error (_("Error setting SASL external user name"));
      return -1;
    }
  }

  return 0;
}