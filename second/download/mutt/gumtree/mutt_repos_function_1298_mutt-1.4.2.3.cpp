int imap_open_connection (IMAP_DATA* idata)
{
  char buf[LONG_STRING];

  if (mutt_socket_open (idata->conn) < 0)
    return -1;

  idata->state = IMAP_CONNECTED;

  if (imap_cmd_step (idata) != IMAP_CMD_CONTINUE)
    goto bail;

  if (ascii_strncasecmp ("* OK", idata->cmd.buf, 4) == 0)
  {
    /* TODO: Parse new tagged CAPABILITY data (* OK [CAPABILITY...]) */
    if (imap_check_capabilities (idata))
      goto bail;
#if defined(USE_SSL) && !defined(USE_NSS)
    /* Attempt STARTTLS if available and desired. */
    if (mutt_bit_isset (idata->capabilities, STARTTLS) && !idata->conn->ssf)
    {
      int rc;

      if ((rc = query_quadoption (OPT_SSLSTARTTLS,
        _("Secure connection with TLS?"))) == -1)
	goto err_close_conn;
      if (rc == M_YES) {
	if ((rc = imap_exec (idata, "STARTTLS", IMAP_CMD_FAIL_OK)) == -1)
	  goto bail;
	if (rc != -2)
	{
	  if (mutt_ssl_starttls (idata->conn))
	  {
	    mutt_error (_("Could not negotiate TLS connection"));
	    mutt_sleep (1);
	    goto bail;
	  }
	  else
	  {
	    /* RFC 2595 demands we recheck CAPABILITY after TLS completes. */
	    if (imap_exec (idata, "CAPABILITY", 0))
	      goto bail;
	  }
	}
      }
    }
#endif    
    if (imap_authenticate (idata))
      goto bail;
    if (idata->conn->ssf)
      dprint (2, (debugfile, "Communication encrypted at %d bits\n",
	idata->conn->ssf));
  }
  else if (ascii_strncasecmp ("* PREAUTH", idata->cmd.buf, 9) == 0)
  {
    if (imap_check_capabilities (idata) != 0)
      goto bail;
  } 
  else
  {
    imap_error ("imap_open_connection()", buf);
    goto bail;
  }

  FREE (&idata->capstr);
  idata->state = IMAP_AUTHENTICATED;

  imap_get_delim (idata);
  return 0;

 err_close_conn:
  mutt_socket_close (idata->conn);
 bail:
  FREE (&idata->capstr);
  idata->state = IMAP_DISCONNECTED;
  return -1;
}