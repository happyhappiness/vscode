void mutt_account_tourl (ACCOUNT* account, ciss_url_t* url)
{
  url->scheme = U_UNKNOWN;
  url->user = NULL;
  url->pass = NULL;
  url->port = 0;

#ifdef USE_IMAP
  if (account->type == M_ACCT_TYPE_IMAP)
  {
    if (account->flags & M_ACCT_SSL)
      url->scheme = U_IMAPS;
    else
      url->scheme = U_IMAP;
  }
#endif

#ifdef USE_POP
  if (account->type == M_ACCT_TYPE_POP)
  {
    if (account->flags & M_ACCT_SSL)
      url->scheme = U_POPS;
    else
      url->scheme = U_POP;
  }
#endif

#ifdef USE_SMTP
  if (account->type == M_ACCT_TYPE_SMTP)
  {
    if (account->flags & M_ACCT_SSL)
      url->scheme = U_SMTPS;
    else
      url->scheme = U_SMTP;
  }
#endif

  url->host = account->host;
  if (account->flags & M_ACCT_PORT)
    url->port = account->port;
  if (account->flags & M_ACCT_USER)
    url->user = account->user;
  if (account->flags & M_ACCT_PASS)
    url->pass = account->pass;
}