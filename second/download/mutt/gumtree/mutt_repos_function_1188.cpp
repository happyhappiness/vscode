static size_t lwslen (const char *s, size_t n)
{
  const char *p = s;
  size_t len = n;

  if (n <= 0)
    return 0;

  for (; p < s + n; p++)
    if (!strchr (" \t\r\n", *p))
    {
      len = (size_t)(p - s);
      break;
    }
  if (strchr ("\r\n", *(p-1))) /* LWS doesn't end with CRLF */
    len = (size_t)0;
  return len;
}