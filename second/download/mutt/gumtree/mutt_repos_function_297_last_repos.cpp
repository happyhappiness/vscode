int mutt_account_fromurl (ACCOUNT* account, ciss_url_t* url)
{
  /* must be present */
  if (url->host)
    strfcpy (account->host, url->host, sizeof (account->host));
  else
    return -1;

  if (url->user)
  {
    strfcpy (account->user, url->user, sizeof (account->user));
    account->flags |= MUTT_ACCT_USER;
  }
  if (url->pass)
  {
    strfcpy (account->pass, url->pass, sizeof (account->pass));
    account->flags |= MUTT_ACCT_PASS;
  }
  if (url->port)
  {
    account->port = url->port;
    account->flags |= MUTT_ACCT_PORT;
  }

  return 0;
}