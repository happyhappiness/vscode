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
    if (!n)
      continue;

    t = safe_malloc (n + 1);
    memcpy (t, p, n);
    t[n] = '\0';

    n = convert_string (u, ulen, fromcode, t, &s, &slen);
    if (n == (size_t)(-1))
    {
      FREE (&t);
      continue;
    }

    if (!tocode || n < bestn)
    {
      bestn = n;
      FREE (&tocode);
      tocode = t;
      if (d)
      {
	FREE (&e);
	e = s;
      }
      else
	FREE (&s);
      elen = slen;
      if (!bestn)
	break;
    }
    else
    {
      FREE (&t);
      FREE (&s);
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