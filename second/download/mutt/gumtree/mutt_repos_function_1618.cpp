static int smtp_helo (CONNECTION* conn)
{
  char buf[LONG_STRING];
  const char* fqdn;

  memset (Capabilities, 0, sizeof (Capabilities));

  if (!Esmtp)
  {
    /* if TLS or AUTH are requested, use EHLO */
    if (conn->account.flags & MUTT_ACCT_USER)
      Esmtp = 1;
#ifdef USE_SSL
    if (option (OPTSSLFORCETLS) || quadoption (OPT_SSLSTARTTLS) != MUTT_NO)
      Esmtp = 1;
#endif
  }

  if(!(fqdn = mutt_fqdn (0)))
    fqdn = NONULL (Hostname);

  snprintf (buf, sizeof (buf), "%s %s\r\n", Esmtp ? "EHLO" : "HELO", fqdn);
  /* XXX there should probably be a wrapper in mutt_socket.c that
    * repeatedly calls conn->write until all data is sent.  This
    * currently doesn't check for a short write.
    */
  if (mutt_socket_write (conn, buf) == -1)
    return smtp_err_write;
  return smtp_get_resp (conn);
}