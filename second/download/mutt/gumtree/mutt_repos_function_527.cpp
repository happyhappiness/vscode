int mx_is_pop (const char *p)
{
  url_scheme_t scheme;

  if (!p)
    return 0;

  scheme = url_check_scheme (p);
  if (scheme == U_POP || scheme == U_POPS)
    return 1;

  return 0;
}