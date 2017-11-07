int iswprint (wint_t wc)
{
  if (Charset_is_utf8 || charset_is_ja)
    return ((0x20 <= wc && wc < 0x7f) || 0xa0 <= wc);
  else
    return (0 <= wc && wc < 256) ? IsPrint (wc) : 0;
}