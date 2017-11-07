int pop_parse_path (const char* path, ACCOUNT* acct)
{
  ciss_url_t url;
  char *c;
  int ret = -1;

  /* Defaults */
  acct->flags = 0;
  acct->port = POP_PORT;
  acct->type = M_ACCT_TYPE_POP;

  c = safe_strdup (path);
  url_parse_ciss (&url, c);

  if (url.scheme == U_POP || url.scheme == U_POPS)
  {
    if (url.scheme == U_POPS)
    {
      acct->flags |= M_ACCT_SSL;
      acct->port = POP_SSL_PORT;
    }

    if ((!url.path || !*url.path) && mutt_account_fromurl (acct, &url) == 0)
      ret = 0;
  }

  FREE (&c);
  return ret;
}