void rfc2047_decode (char **pd)
{
  const char *p, *q;
  size_t m, n;
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
      if (option (OPTIGNORELWS))
      {
        n = mutt_strlen (s);
        if (found_encoded && (m = lwslen (s, n)) != 0)
        {
          if (m != n)
            *d = ' ', d++, dlen--;
          s += m;
        }
      }
      if (AssumedCharset && *AssumedCharset)
      {
	char *t;
	size_t tlen;

	n = mutt_strlen (s);
	t = safe_malloc (n + 1);
	strfcpy (t, s, n + 1);
	convert_nonmime_string (&t);
	tlen = mutt_strlen (t);
	strncpy (d, t, tlen);
	d += tlen;
	FREE (&t);
	break;
      }
      strncpy (d, s, dlen);
      d += dlen;
      break;
    }

    if (p != s)
    {
      n = (size_t) (p - s);
      /* ignore spaces between encoded word
       * and linear-white-space between encoded word and *text */
      if (option (OPTIGNORELWS))
      {
        if (found_encoded && (m = lwslen (s, n)) != 0)
        {
          if (m != n)
            *d = ' ', d++, dlen--;
          n -= m, s += m;
        }

        if ((m = n - lwsrlen (s, n)) != 0)
        {
          if (m > dlen)
            m = dlen;
          memcpy (d, s, m);
          d += m;
          dlen -= m;
          if (m != n)
            *d = ' ', d++, dlen--;
        }
      }
      else if (!found_encoded || strspn (s, " \t\r\n") != n)
      {
	if (n > dlen)
	  n = dlen;
	memcpy (d, s, n);
	d += n;
	dlen -= n;
      }
    }

    if (rfc2047_decode_word (d, p, dlen) == -1)
    {
      /* could not decode word, fall back to displaying the raw string */
      strfcpy(d, p, dlen);
    }
    found_encoded = 1;
    s = q;
    n = mutt_strlen (d);
    dlen -= n;
    d += n;
  }
  *d = 0;

  FREE (pd);		/* __FREE_CHECKED__ */
  *pd = d0;
  mutt_str_adjust (pd);
}