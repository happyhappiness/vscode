void mutt_set_charset (char *charset)
{
  char buffer[STRING];

  mutt_canonical_charset (buffer, sizeof (buffer), charset);

  Charset_is_utf8 = 0;
#ifndef HAVE_WC_FUNCS
  charset_is_ja = 0;
  if (charset_to_utf8 != (iconv_t)(-1))
  {
    iconv_close (charset_to_utf8);
    charset_to_utf8 = (iconv_t)(-1);
  }
  if (charset_from_utf8 != (iconv_t)(-1))
  {
    iconv_close (charset_from_utf8);
    charset_from_utf8 = (iconv_t)(-1);
  }
#endif

  if (!strcmp(buffer, "utf-8"))
    Charset_is_utf8 = 1;
#ifndef HAVE_WC_FUNCS
  else if (!strcmp(buffer, "euc-jp") || !strcmp(buffer, "shift_jis"))
  {
    charset_is_ja = 1;
    charset_to_utf8 = iconv_open ("UTF-8", charset);
    charset_from_utf8 = iconv_open (charset, "UTF-8");
  }
#endif

#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
  bind_textdomain_codeset(PACKAGE, buffer);
#endif
}