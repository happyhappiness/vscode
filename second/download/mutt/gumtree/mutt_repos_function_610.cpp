wint_t towupper (wint_t wc)
{
  if (Charset_is_utf8 || charset_is_ja)
    return towupper_ucs (wc);
  else
    return (0 <= wc && wc < 256) ? toupper (wc) : wc;
}