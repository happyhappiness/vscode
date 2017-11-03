int mutt_check_charset (const char *s, int strict)
{
  int i;
  iconv_t cd;

  if (mutt_is_utf8 (s))
    return 0;

  if (!strict)
    for (i = 0; PreferredMIMENames[i].key; i++)
    {
      if (ascii_strcasecmp (PreferredMIMENames[i].key, s) == 0 ||
	  ascii_strcasecmp (PreferredMIMENames[i].pref, s) == 0)
	return 0;
    }

  if ((cd = mutt_iconv_open (s, s, 0)) != (iconv_t)(-1))
  {
    iconv_close (cd);
    return 0;
  }

  return -1;
}