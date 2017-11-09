size_t wcrtomb (char *s, wchar_t wc, mbstate_t *ps)
{
  /* We only handle stateless encodings, so we can ignore ps. */

  if (Charset_is_utf8)
    return mutt_wctoutf8 (s, wc, MB_LEN_MAX);
  else if (charset_from_utf8 != (iconv_t)(-1))
    return wcrtomb_iconv (s, wc, charset_from_utf8);
  else
  {
    if (!s)
      return 1;
    if (wc < 0x100)
    {
      *s = wc;
      return 1;
    }
    errno = EILSEQ;
    return (size_t)(-1);
  }
}