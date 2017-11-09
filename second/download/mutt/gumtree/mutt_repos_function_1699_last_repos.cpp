static int
smtp_get_resp (CONNECTION * conn)
{
  int n;
  char buf[1024];

  do {
    n = mutt_socket_readln (buf, sizeof (buf), conn);
    if (n < 4) {
      /* read error, or no response code */
      return smtp_err_read;
    }

    if (!ascii_strncasecmp ("8BITMIME", buf + 4, 8))
      mutt_bit_set (Capabilities, EIGHTBITMIME);
    else if (!ascii_strncasecmp ("AUTH ", buf + 4, 5))
    {
      mutt_bit_set (Capabilities, AUTH);
      FREE (&AuthMechs);
      AuthMechs = safe_strdup (buf + 9);
    }
    else if (!ascii_strncasecmp ("DSN", buf + 4, 3))
      mutt_bit_set (Capabilities, DSN);
    else if (!ascii_strncasecmp ("STARTTLS", buf + 4, 8))
      mutt_bit_set (Capabilities, STARTTLS);
    else if (!ascii_strncasecmp ("SMTPUTF8", buf + 4, 8))
      mutt_bit_set (Capabilities, SMTPUTF8);

    if (smtp_code (buf, n, &n) < 0)
      return smtp_err_code;

  } while (buf[3] == '-');

  if (smtp_success (n) || n == smtp_continue)
    return 0;

  mutt_error (_("SMTP session failed: %s"), buf);
    return -1;
}