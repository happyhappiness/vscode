url_scheme_t url_check_scheme (const char *s)
{
  char sbuf[STRING];
  char *t;
  int i;

  if (!s || !(t = strchr (s, ':')))
    return U_UNKNOWN;
  if ((size_t)(t - s) >= sizeof (sbuf) - 1)
    return U_UNKNOWN;

  strfcpy (sbuf, s, t - s + 1);
  for (t = sbuf; *t; t++)
    *t = ascii_tolower (*t);

  if ((i = mutt_getvaluebyname (sbuf, UrlMap)) == -1)
    return U_UNKNOWN;
  else
    return (url_scheme_t) i;
}