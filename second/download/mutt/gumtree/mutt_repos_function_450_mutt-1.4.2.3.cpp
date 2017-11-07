int mutt_sasl_client_new (CONNECTION* conn, sasl_conn_t** saslconn)
{
  sasl_security_properties_t secprops;
  sasl_external_properties_t extprops;
  const char* service;
  int rc;

  if (mutt_sasl_start () != SASL_OK)
    return -1;

  switch (conn->account.type)
  {
    case M_ACCT_TYPE_IMAP:
      service = "imap";
      break;
    case M_ACCT_TYPE_POP:
      service = "pop-3";
      break;
    default:
      dprint (1, (debugfile, "mutt_sasl_client_new: account type unset\n"));
      return -1;
  }
  
  rc = sasl_client_new (service, conn->account.host,
    mutt_sasl_get_callbacks (&conn->account), SASL_SECURITY_LAYER, saslconn);
  
  if (rc != SASL_OK)
  {
    dprint (1, (debugfile,
      "mutt_sasl_client_new: Error allocating SASL connection\n"));
    return -1;
  }

  /*** set sasl IP properties, necessary for use with krb4 ***/
  /* Do we need to fail if this fails? I would assume having these unset
   * would just disable KRB4. Who wrote this code? I'm not sure how this
   * interacts with the NSS code either, since that mucks with the fd. */
  {
    struct sockaddr_in local, remote;
    socklen_t size;

    size = sizeof (local);
    if (getsockname (conn->fd, (struct sockaddr*) &local, &size))
      return -1;

    size = sizeof(remote);
    if (getpeername(conn->fd, (struct sockaddr*) &remote, &size))
      return -1;

#ifdef SASL_IP_LOCAL
    if (sasl_setprop(*saslconn, SASL_IP_LOCAL, &local) != SASL_OK)
    {
      dprint (1, (debugfile,
	"mutt_sasl_client_new: Error setting local IP address\n"));
      return -1;
    }
#endif

#ifdef SASL_IP_REMOTE
    if (sasl_setprop(*saslconn, SASL_IP_REMOTE, &remote) != SASL_OK)
    {
      dprint (1, (debugfile,
	"mutt_sasl_client_new: Error setting remote IP address\n"));
      return -1;
    }
#endif
  }

  /* set security properties. We use NOPLAINTEXT globally, since we can
   * just fall back to LOGIN in the IMAP case anyway. If that doesn't
   * work for POP, we can make it a flag or move this code into
   * imap/auth_sasl.c */
  memset (&secprops, 0, sizeof (secprops));
  /* Work around a casting bug in the SASL krb4 module */
  secprops.max_ssf = 0x7fff;
  secprops.maxbufsize = M_SASL_MAXBUF;
  secprops.security_flags |= SASL_SEC_NOPLAINTEXT;
  if (sasl_setprop (*saslconn, SASL_SEC_PROPS, &secprops) != SASL_OK)
  {
    dprint (1, (debugfile,
      "mutt_sasl_client_new: Error setting security properties\n"));
    return -1;
  }

  /* we currently don't have an SSF finder for NSS (I don't know the API).
   * If someone does it'd probably be trivial to write mutt_nss_get_ssf().
   * I have a feeling more SSL code could be shared between those two files,
   * but I haven't looked into it yet, since I still don't know the APIs. */
#if defined(USE_SSL) && !defined(USE_NSS)
  if (conn->account.flags & M_ACCT_SSL)
  {
    memset (&extprops, 0, sizeof (extprops));
    extprops.ssf = conn->ssf;
    dprint (2, (debugfile, "External SSF: %d\n", extprops.ssf));
    if (sasl_setprop (*saslconn, SASL_SSF_EXTERNAL, &extprops) != SASL_OK)
    {
      dprint (1, (debugfile, "mutt_sasl_client_new: Error setting external properties\n"));
      return -1;
    }
  }
#endif

  return 0;
}