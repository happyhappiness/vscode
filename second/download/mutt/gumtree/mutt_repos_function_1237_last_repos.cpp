static size_t lwsrlen (const char *s, size_t n)
{
  const char *p = s + n - 1;
  size_t len = n;

  if (n <= 0)
    return 0;

  if (strchr ("\r\n", *p)) /* LWS doesn't end with CRLF */
    return (size_t)0;

  for (; p >= s; p--)
    if (!strchr (" \t\r\n", *p))
    {
      len = (size_t)(s + n - 1 - p);
      break;
    }
  return len;
}