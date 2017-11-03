static int smtp_fill_account (ACCOUNT* account)
{
  static unsigned short SmtpPort = 0;

  struct servent* service;
  ciss_url_t url;
  char* urlstr;

  account->flags = 0;
  account->port = 0;
  account->type = MUTT_ACCT_TYPE_SMTP;

  urlstr = safe_strdup (SmtpUrl);
  url_parse_ciss (&url, urlstr);
  if ((url.scheme != U_SMTP && url.scheme != U_SMTPS)
      || mutt_account_fromurl (account, &url) < 0)
  {
    FREE (&urlstr);
    mutt_error (_("Invalid SMTP URL: %s"), SmtpUrl);
    mutt_sleep (1);
    return -1;
  }
  FREE (&urlstr);

  if (url.scheme == U_SMTPS)
    account->flags |= MUTT_ACCT_SSL;

  if (!account->port)
  {
    if (account->flags & MUTT_ACCT_SSL)
      account->port = SMTPS_PORT;
    else
    {
      if (!SmtpPort)
      {
        service = getservbyname ("smtp", "tcp");
        if (service)
          SmtpPort = ntohs (service->s_port);
        else
          SmtpPort = SMTP_PORT;
        dprint (3, (debugfile, "Using default SMTP port %d\n", SmtpPort));
      }
      account->port = SmtpPort;
    }
  }

  return 0;
}