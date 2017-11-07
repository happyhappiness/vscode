int mutt_strwidth (const char *s)
{
  wchar_t wc;
  int w;
  size_t k, n;
  mbstate_t mbstate;

  if (!s) return 0;

  n = mutt_strlen (s);

  memset (&mbstate, 0, sizeof (mbstate));
  for (w=0; n && (k = mbrtowc (&wc, s, n, &mbstate)); s += k, n -= k)
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      if (k == (size_t)(-1))
        memset (&mbstate, 0, sizeof (mbstate));
      k = (k == (size_t)(-1)) ? 1 : n;
      wc = replacement_char ();
    }
    if (!IsWPrint (wc))
      wc = '?';
    w += wcwidth (wc);
  }
  return w;
}