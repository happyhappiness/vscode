int mx_is_imap(const char *p)
{
  url_scheme_t scheme;

  if (!p)
    return 0;

  if (*p == '{')
    return 1;

  scheme = url_check_scheme (p);
  if (scheme == U_IMAP || scheme == U_IMAPS)
    return 1;

  return 0;
}