static int
mutt_nss_socket_open (CONNECTION * con)
{
  mutt_nss_t *sockdata;
  PRNetAddr addr;
  struct hostent *he;

  memset (&addr, 0, sizeof (addr));
  addr.inet.family = AF_INET;
  addr.inet.port = PR_htons (con->account.port);
  he = gethostbyname (con->account.host);
  if (!he)
  {
    mutt_error (_("Unable to find ip for host %s"), con->account.host);
    return -1;
  }
  addr.inet.ip = *((int *) he->h_addr_list[0]);

  sockdata = safe_calloc (1, sizeof (mutt_nss_t));

  do
  {
    sockdata->fd = PR_NewTCPSocket ();
    if (sockdata->fd == NULL)
    {
      mutt_error (_("PR_NewTCPSocket failed."));
      break;
    }
    /* make this a SSL socket */
    sockdata->fd = SSL_ImportFD (NULL, sockdata->fd);
    
    /* set SSL version options based upon user's preferences */
    if (!option (OPTTLSV1))
      SSL_OptionSet (sockdata->fd, SSL_ENABLE_TLS, PR_FALSE);
    
    if (!option (OPTSSLV2))
      SSL_OptionSet (sockdata->fd, SSL_ENABLE_SSL2, PR_FALSE);

    if (!option (OPTSSLV3))
      SSL_OptionSet (sockdata->fd, SSL_ENABLE_SSL3, PR_FALSE);
    
    /* set the host we were attempting to connect to in order to verify
     * the name in the certificate we get back.
     */
    if (SSL_SetURL (sockdata->fd, con->account.host))
    {
      mutt_nss_error ("SSL_SetURL");
      break;
    }

    /* we don't need no stinking pin.  we don't authenticate ourself
     * via SSL.
     */
    SSL_SetPKCS11PinArg (sockdata->fd, 0);
    
    sockdata->db = CERT_GetDefaultCertDB ();
    
    /* use the default supplied hook.  it takes an argument to our
     * certificate database.  the manual lies, you can't really specify
     * NULL for the callback to get the default!
     */
    SSL_AuthCertificateHook (sockdata->fd, SSL_AuthCertificate,
			     sockdata->db);
    /* set the callback to be used when SSL_AuthCertificate() fails.  this
     * allows us to override and insert the cert back into the db
     */
    SSL_BadCertHook (sockdata->fd, mutt_nss_bad_cert, sockdata->db);
    
    if (PR_Connect (sockdata->fd, &addr, PR_INTERVAL_NO_TIMEOUT) ==
	PR_FAILURE)
    {
      mutt_error (_("Unable to connect to host %s"), con->account.host);
      break;
    }
    
    /* store the extra info in the CONNECTION struct for later use. */
    con->sockdata = sockdata;
    
    /* HACK.  some of the higher level calls in mutt_socket.c depend on this
     * being >0 when we are in the connected state.  we just set this to
     * an arbitrary value to avoid hitting that bug, since we neve have the
     * real fd.
     */
    con->fd = 42;
    
    /* success */
    return 0;
  }
  while (0);
  
  /* we get here when we had an oops.  clean up the mess. */

  if (sockdata)
  {
    if (sockdata->fd)
      PR_Close (sockdata->fd);
    if (sockdata->db)
      CERT_ClosePermCertDB (sockdata->db);
    safe_free ((void **) &sockdata);
  }
  return -1;
}