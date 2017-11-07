void rfc2047_decode (char **pd)
{
  const char *p, *q;
  size_t n;
  int found_encoded = 0;
  char *d0, *d;
  const char *s = *pd;
  size_t dlen;

  if (!s || !*s)
    return;

  dlen = 4 * strlen (s); /* should be enough */
  d = d0 = safe_malloc (dlen + 1);

  while (*s && dlen > 0)
  {
    if (!(p = find_encoded_word (s, &q)))
    {
      /* no encoded words */
      strncpy (d, s, dlen);
      d += dlen;
      break;
    }

    if (p != s)
    {
      n = (size_t) (p - s);
      /* ignore spaces between encoded words */
      if (!found_encoded || strspn (s, " \t\r\n") != n)
      {
	if (n > dlen)
	  n = dlen;
	memcpy (d, s, n);
	d += n;
	dlen -= n;
      }
    }

    rfc2047_decode_word (d, p, dlen);
    found_encoded = 1;
    s = q;
    n = mutt_strlen (d);
    dlen -= n;
    d += n;
  }
  *d = 0;

  safe_free ((void **) pd);
  *pd = d0;
  mutt_str_adjust (pd);
}