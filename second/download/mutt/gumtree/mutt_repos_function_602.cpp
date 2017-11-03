size_t mbrtowc (wchar_t *pwc, const char *s, size_t n, mbstate_t *ps)
{
  static mbstate_t mbstate;

  if (!ps)
    ps = &mbstate;

  if (Charset_is_utf8)
    return utf8rtowc (pwc, s, n, ps);
  else if (charset_to_utf8 != (iconv_t)(-1))
    return mbrtowc_iconv (pwc, s, n, ps, charset_to_utf8);
  else
  {
    if (!s)
    {
      memset(ps, 0, sizeof(*ps));
      return 0;
    }
    if (!n)
      return (size_t)-2;
    if (pwc)
      *pwc = (wchar_t)(unsigned char)*s;
    return (*s != 0);
  }
}