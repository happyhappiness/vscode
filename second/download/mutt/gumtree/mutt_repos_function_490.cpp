void mutt_format_string (char *dest, size_t destlen,
			 int min_width, int max_width,
			 int justify, char m_pad_char,
			 const char *s, size_t n,
			 int arboreal)
{
  char *p;
  wchar_t wc;
  int w;
  size_t k, k2;
  char scratch[MB_LEN_MAX];
  mbstate_t mbstate1, mbstate2;

  memset(&mbstate1, 0, sizeof (mbstate1));
  memset(&mbstate2, 0, sizeof (mbstate2));
  --destlen;
  p = dest;
  for (; n && (k = mbrtowc (&wc, s, n, &mbstate1)); s += k, n -= k)
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      if (k == (size_t)(-1) && errno == EILSEQ)
	memset (&mbstate1, 0, sizeof (mbstate1));

      k = (k == (size_t)(-1)) ? 1 : n;
      wc = replacement_char ();
    }
    if (arboreal && wc < MUTT_TREE_MAX)
      w = 1; /* hack */
    else
    {
#ifdef HAVE_ISWBLANK
      if (iswblank (wc))
	wc = ' ';
      else
#endif
      if (!IsWPrint (wc))
	wc = '?';
      w = wcwidth (wc);
    }
    if (w >= 0)
    {
      if (w > max_width || (k2 = wcrtomb (scratch, wc, &mbstate2)) > destlen)
	break;
      min_width -= w;
      max_width -= w;
      strncpy (p, scratch, k2);
      p += k2;
      destlen -= k2;
    }
  }
  w = (int)destlen < min_width ? destlen : min_width;
  if (w <= 0)
    *p = '\0';
  else if (justify == FMT_RIGHT)	/* right justify */
  {
    p[w] = '\0';
    while (--p >= dest)
      p[w] = *p;
    while (--w >= 0)
      dest[w] = m_pad_char;
  }
  else if (justify == FMT_CENTER)	/* center */
  {
    char *savedp = p;
    int half = (w+1) / 2; /* half of cushion space */

    p[w] = '\0';

    /* move str to center of buffer */
    while (--p >= dest)
      p[half] = *p;

    /* fill rhs */
    p = savedp + half;
    while (--w >= half)
      *p++ = m_pad_char;

    /* fill lhs */
    while (half--)
      dest[half] = m_pad_char;
  }
  else					/* left justify */
  {
    while (--w >= 0)
      *p++ = m_pad_char;
    *p = '\0';
  }
}