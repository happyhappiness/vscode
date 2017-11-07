static int my_width (const char *str, int col, int flags)
{
  wchar_t wc;
  int l, w = 0, nl = 0;
  const char *p = str;

  while (p && *p)
  {
    if (mbtowc (&wc, p, MB_CUR_MAX) >= 0)
    {
      l = wcwidth (wc);
      if (l < 0)
	l = 1;
      /* correctly calc tab stop, even for sending as the
       * line should look pretty on the receiving end */
      if (wc == L'\t' || (nl && wc == L' '))
      {
	nl = 0;
	l = 8 - (col % 8);
      }
      /* track newlines for display-case: if we have a space
       * after a newline, assume 8 spaces as for display we
       * always tab-fold */
      else if ((flags & CH_DISPLAY) && wc == '\n')
	nl = 1;
    }
    else
      l = 1;
    w += l;
    p++;
  }
  return w;
}