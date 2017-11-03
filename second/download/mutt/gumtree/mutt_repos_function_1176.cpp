int convert_nonmime_string (char **ps)
{
  const char *c, *c1;

  for (c = AssumedCharset; c; c = c1 ? c1 + 1 : 0)
  {
    char *u = *ps;
    char *s;
    char *fromcode;
    size_t m, n;
    size_t ulen = mutt_strlen (*ps);
    size_t slen;

    if (!u || !*u)
      return 0;

    c1 = strchr (c, ':');
    n = c1 ? c1 - c : mutt_strlen (c);
    if (!n)
      return 0;
    fromcode = safe_malloc (n + 1);
    strfcpy (fromcode, c, n + 1);
    m = convert_string (u, ulen, fromcode, Charset, &s, &slen);
    FREE (&fromcode);
    if (m != (size_t)(-1))
    {
      FREE (ps); /* __FREE_CHECKED__ */
      *ps = s;
      return 0;
    }
  }
  mutt_convert_string (ps,
      (const char *)mutt_get_default_charset (),
      Charset, MUTT_ICONV_HOOK_FROM);
  return -1;
}