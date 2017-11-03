int iswupper (wint_t wc)
{
  if (Charset_is_utf8 || charset_is_ja)
    return iswupper_ucs (wc);
  else
    return (0 <= wc && wc < 256) ? isupper (wc) : 0;
}