char *mutt_get_default_charset ()
{
  static char fcharset[SHORT_STRING];
  const char *c = AssumedCharset;
  const char *c1;

  if (c && *c) {
    c1 = strchr (c, ':');
    strfcpy (fcharset, c, c1 ? (c1 - c + 1) : sizeof (fcharset));
    return fcharset;
  }
  return strcpy (fcharset, "us-ascii"); /* __STRCPY_CHECKED__ */
}