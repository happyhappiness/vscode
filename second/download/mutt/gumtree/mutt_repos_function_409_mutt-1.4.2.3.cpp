int iswalnum (wint_t wc)
{
  if (Charset_is_utf8 || charset_is_ja)
    return iswalnum_ucs (wc);
  else
    return (0 <= wc && wc < 256) ? isalnum (wc) : 0;
}