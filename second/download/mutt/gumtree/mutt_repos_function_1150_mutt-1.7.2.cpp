static int check_idn (char *domain)
{
  if (! domain)
    return 0;

  if (ascii_strncasecmp (domain, "xn--", 4) == 0)
    return 1;

  while ((domain = strchr (domain, '.')) != NULL)
  {
    if (ascii_strncasecmp (++domain, "xn--", 4) == 0)
      return 1;
  }

  return 0;
}