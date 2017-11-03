int
mutt_smtp_send (const ADDRESS* from, const ADDRESS* to, const ADDRESS* cc,
                const ADDRESS* bcc, const char *msgfile, int eightbit)
{
  CONNECTION *conn;
  ACCOUNT account;
  const char* envfrom;
  char buf[1024];
  int ret = -1;

  /* it might be better to synthesize an envelope from from user and host
   * but this condition is most likely arrived at accidentally */
  if (EnvFrom)
    envfrom = EnvFrom->mailbox;
  else if (from)
    envfrom = from->mailbox;
  else
  {
    mutt_error (_("No from address given"));
    return -1;
  }

  if (smtp_fill_account (&account) < 0)
    return ret;

  if (!(conn = mutt_conn_find (NULL, &account)))
    return -1;

  Esmtp = eightbit;

  do
  {
    /* send our greeting */
    if (( ret = smtp_open (conn)))
      break;
    FREE (&AuthMechs);

    /* send the sender's address */
    ret = snprintf (buf, sizeof (buf), "MAIL FROM:<%s>", envfrom);
    if (eightbit && mutt_bit_isset (Capabilities, EIGHTBITMIME))
    {
      safe_strncat (buf, sizeof (buf), " BODY=8BITMIME", 15);
      ret += 14;
    }
    if (DsnReturn && mutt_bit_isset (Capabilities, DSN))
      ret += snprintf (buf + ret, sizeof (buf) - ret, " RET=%s", DsnReturn);
    if (mutt_bit_isset (Capabilities, SMTPUTF8) &&
	(address_uses_unicode(envfrom) ||
	 addresses_use_unicode(to) ||
	 addresses_use_unicode(cc) ||
	 addresses_use_unicode(bcc)))
      ret += snprintf (buf + ret, sizeof (buf) - ret, " SMTPUTF8");
    safe_strncat (buf, sizeof (buf), "\r\n", 3);
    if (mutt_socket_write (conn, buf) == -1)
    {
      ret = smtp_err_write;
      break;
    }
    if ((ret = smtp_get_resp (conn)))
      break;

    /* send the recipient list */
    if ((ret = smtp_rcpt_to (conn, to)) || (ret = smtp_rcpt_to (conn, cc))
        || (ret = smtp_rcpt_to (conn, bcc)))
      break;

    /* send the message data */
    if ((ret = smtp_data (conn, msgfile)))
      break;

    mutt_socket_write (conn, "QUIT\r\n");

    ret = 0;
  }
  while (0);

  if (conn)
    mutt_socket_close (conn);

  if (ret == smtp_err_read)
    mutt_error (_("SMTP session failed: read error"));
  else if (ret == smtp_err_write)
    mutt_error (_("SMTP session failed: write error"));
  else if (ret == smtp_err_code)
    mutt_error (_("Invalid server response"));

  return ret;
}