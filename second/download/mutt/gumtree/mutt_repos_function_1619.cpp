static int smtp_open (CONNECTION* conn)
{
  int rc;

  if (mutt_socket_open (conn))
    return -1;

  /* get greeting string */
  if ((rc = smtp_get_resp (conn)))
    return rc;

  if ((rc = smtp_helo (conn)))
    return rc;

#ifdef USE_SSL
  if (conn->ssf)
    rc = MUTT_NO;
  else if (option (OPTSSLFORCETLS))
    rc = MUTT_YES;
  else if (mutt_bit_isset (Capabilities, STARTTLS) &&
           (rc = query_quadoption (OPT_SSLSTARTTLS,
                                   _("Secure connection with TLS?"))) == -1)
    return rc;

  if (rc == MUTT_YES)
  {
    if (mutt_socket_write (conn, "STARTTLS\r\n") < 0)
      return smtp_err_write;
    if ((rc = smtp_get_resp (conn)))
      return rc;

    if (mutt_ssl_starttls (conn))
    {
      mutt_error (_("Could not negotiate TLS connection"));
      mutt_sleep (1);
      return -1;
    }

    /* re-EHLO to get authentication mechanisms */
    if ((rc = smtp_helo (conn)))
      return rc;
  }
#endif

  if (conn->account.flags & MUTT_ACCT_USER)
  {
    if (!mutt_bit_isset (Capabilities, AUTH))
    {
      mutt_error (_("SMTP server does not support authentication"));
      mutt_sleep (1);
      return -1;
    }

#ifdef USE_SASL
    return smtp_auth (conn);
#else
    mutt_error (_("SMTP authentication requires SASL"));
    mutt_sleep (1);
    return -1;
#endif /* USE_SASL */
  }

  return 0;
}