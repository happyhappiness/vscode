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

  if (mutt_is_utf8 (buffer))
    Charset_is_utf8 = 1;
#ifndef HAVE_WC_FUNCS
  else if (!ascii_strcasecmp(buffer, "euc-jp") || !ascii_strcasecmp(buffer, "shift_jis")
  	|| !ascii_strcasecmp(buffer, "cp932") || !ascii_strcasecmp(buffer, "eucJP-ms"))
  {
    charset_is_ja = 1;

    /* Note flags=0 to skip charset-hooks: User masters the $charset
     * name, and we are sure of our "utf-8" constant. So there is no
     * possibility of wrong name that we would want to try to correct
     * with a charset-hook. Or rather: If $charset was wrong, we would
     * want to try to correct... $charset directly.
     */
    charset_to_utf8 = mutt_iconv_open ("utf-8", charset, 0);
    charset_from_utf8 = mutt_iconv_open (charset, "utf-8", 0);
  }
#endif

#if defined(HAVE_BIND_TEXTDOMAIN_CODESET) && defined(ENABLE_NLS)
  bind_textdomain_codeset(PACKAGE, buffer);
#endif
}