void mutt_paddstr (int n, const char *s)
{
  wchar_t wc;
  int w;
  size_t k;
  size_t len = mutt_strlen (s);
  mbstate_t mbstate;

  memset (&mbstate, 0, sizeof (mbstate));
  for (; len && (k = mbrtowc (&wc, s, len, &mbstate)); s += k, len -= k)
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      if (k == (size_t) (-1))
	memset (&mbstate, 0, sizeof (mbstate));
      k = (k == (size_t)(-1)) ? 1 : len;
      wc = replacement_char ();
    }
    if (!IsWPrint (wc))
      wc = '?';
    w = wcwidth (wc);
    if (w >= 0)
    {
      if (w > n)
	break;
      addnstr ((char *)s, k);
      n -= w;
    }
  }
  while (n-- > 0)
    addch (' ');
}