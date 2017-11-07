char *mutt_choose_charset (const char *fromcode, const char *charsets,
		      char *u, size_t ulen, char **d, size_t *dlen)
{
  char canonical_buff[LONG_STRING];
  char *e = 0, *tocode = 0;
  size_t elen = 0, bestn = 0;
  const char *p, *q;

  for (p = charsets; p; p = q ? q + 1 : 0)
  {
    char *s, *t;
    size_t slen, n;

    q = strchr (p, ':');

    n = q ? q - p : strlen (p);

    if (!n ||
	/* Assume that we never need more than 12 characters of
	   encoded-text to encode a single character. */
	n > (ENCWORD_LEN_MAX - ENCWORD_LEN_MIN + 2 - 12))
      continue;

    t = safe_malloc (n + 1);
    memcpy (t, p, n);
    t[n] = '\0';

    n = convert_string (u, ulen, fromcode, t, &s, &slen);
    if (n == (size_t)(-1))
      continue;

    if (!tocode || n < bestn)
    {
      bestn = n;
      safe_free ((void **) &tocode);
      tocode = t;
      if (d)
      {
	safe_free ((void **) &e);
	e = s;
      }
      else
	safe_free ((void **) &s);
      elen = slen;
      if (!bestn)
	break;
    }
    else
    {
      safe_free ((void **) &t);
      safe_free ((void **) &s);
    }
  }
  if (tocode)
  {
    if (d)
      *d = e;
    if (dlen)
      *dlen = elen;
    
    mutt_canonical_charset (canonical_buff, sizeof (canonical_buff), tocode);
    mutt_str_replace (&tocode, canonical_buff);
  }
  return tocode;
}