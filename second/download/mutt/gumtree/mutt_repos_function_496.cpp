int mutt_charlen (const char *s, int *width)
{
  wchar_t wc;
  mbstate_t mbstate;
  size_t k, n;

  if (!s || !*s)
    return 0;

  n = mutt_strlen (s);
  memset (&mbstate, 0, sizeof (mbstate));
  k = mbrtowc (&wc, s, n, &mbstate);
  if (width)
    *width = wcwidth (wc);
  return (k == (size_t)(-1) || k == (size_t)(-2)) ? -1 : k;
}