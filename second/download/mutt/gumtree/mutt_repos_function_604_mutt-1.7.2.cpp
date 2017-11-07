int iswspace (wint_t wc)
{
  if (Charset_is_utf8 || charset_is_ja)
    return (9 <= wc && wc <= 13) || wc == 32;
  else
    return (0 <= wc && wc < 256) ? isspace (wc) : 0;
}