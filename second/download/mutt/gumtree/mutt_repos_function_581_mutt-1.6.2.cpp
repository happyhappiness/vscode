static size_t wcrtomb_iconv (char *s, wchar_t wc, iconv_t cd)
{
  char buf[MB_LEN_MAX+1];
  ICONV_CONST char *ib;
  char *ob;
  size_t ibl, obl, r;

  if (s)
  {
    ibl = mutt_wctoutf8 (buf, wc, sizeof (buf));
    if (ibl == (size_t)(-1))
      return (size_t)(-1);
    ib = buf;
    ob = s;
    obl = MB_LEN_MAX;
    r = iconv (cd, &ib, &ibl, &ob, &obl);
  }
  else
  {
    ib = "";
    ibl = 1;
    ob = buf;
    obl = sizeof (buf);
    r = iconv (cd, &ib, &ibl, &ob, &obl);
  }
  return ob - s;
}