static int print_macro (FILE *f, int maxwidth, const char **macro)
{
  int n = maxwidth;
  wchar_t wc;
  int w;
  size_t k;
  size_t len = mutt_strlen (*macro);
  mbstate_t mbstate1, mbstate2;

  memset (&mbstate1, 0, sizeof (mbstate1));
  memset (&mbstate2, 0, sizeof (mbstate2));
  for (; len && (k = mbrtowc (&wc, *macro, len, &mbstate1)); *macro += k, len -= k)
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      if (k == (size_t)(-1))
        memset (&mbstate1, 0, sizeof (mbstate1));
      k = (k == (size_t)(-1)) ? 1 : len;
      wc = replacement_char ();
    }
    /* glibc-2.1.3's wcwidth() returns 1 for unprintable chars! */
    if (IsWPrint (wc) && (w = wcwidth (wc)) >= 0)
    {
      if (w > n)
	break;
      n -= w;
      {
	char buf[MB_LEN_MAX*2];
	size_t n1, n2;
	if ((n1 = wcrtomb (buf, wc, &mbstate2)) != (size_t)(-1) &&
	    (n2 = wcrtomb (buf + n1, 0, &mbstate2)) != (size_t)(-1))
	  fputs (buf, f);
      }
    }
    else if (wc < 0x20 || wc == 0x7f)
    {
      if (2 > n)
	break;
      n -= 2;
      if (wc == '\033')
	fprintf (f, "\\e");
      else if (wc == '\n')
	fprintf (f, "\\n");
      else if (wc == '\r')
	fprintf (f, "\\r");
      else if (wc == '\t')
	fprintf (f, "\\t");
      else
	fprintf (f, "^%c", (char)((wc + '@') & 0x7f));
    }
    else
    {
      if (1 > n)
	break;
      n -= 1;
      fprintf (f, "?");
    }
  }
  return (maxwidth - n);
}