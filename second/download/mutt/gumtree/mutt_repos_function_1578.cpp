int pop_parse_path (const char* path, ACCOUNT* acct)
{
  ciss_url_t url;
  char *c;
  struct servent *service;

  /* Defaults */
  acct->flags = 0;
  acct->type = MUTT_ACCT_TYPE_POP;
  acct->port = 0;

  c = safe_strdup (path);
  url_parse_ciss (&url, c);

  if ((url.scheme != U_POP && url.scheme != U_POPS) ||
      mutt_account_fromurl (acct, &url) < 0)
  {
    FREE(&c);
    mutt_error(_("Invalid POP URL: %s\n"), path);
    mutt_sleep(1);
    return -1;
  }

  if (url.scheme == U_POPS)
    acct->flags |= MUTT_ACCT_SSL;

  service = getservbyname (url.scheme == U_POP ? "pop3" : "pop3s", "tcp");
  if (!acct->port) {
    if (service)
      acct->port = ntohs (service->s_port);
    else
      acct->port = url.scheme == U_POP ? POP_PORT : POP_SSL_PORT;;
  }

  FREE (&c);
  return 0;
}