iconv_t mutt_iconv_open (const char *tocode, const char *fromcode, int flags)
{
  char tocode1[SHORT_STRING];
  char fromcode1[SHORT_STRING];
  char *tocode2, *fromcode2;
  char *tmp;

  iconv_t cd;

  /* transform to MIME preferred charset names */
  mutt_canonical_charset (tocode1, sizeof (tocode1), tocode);
  mutt_canonical_charset (fromcode1, sizeof (fromcode1), fromcode);

  /* maybe apply charset-hooks and recanonicalise fromcode,
   * but only when caller asked us to sanitize a potentialy wrong
   * charset name incoming from the wild exterior. */
  if ((flags & MUTT_ICONV_HOOK_FROM) && (tmp = mutt_charset_hook (fromcode1)))
    mutt_canonical_charset (fromcode1, sizeof (fromcode1), tmp);

  /* always apply iconv-hooks to suit system's iconv tastes */
  tocode2 = mutt_iconv_hook (tocode1);
  tocode2 = (tocode2) ? tocode2 : tocode1;
  fromcode2 = mutt_iconv_hook (fromcode1);
  fromcode2 = (fromcode2) ? fromcode2 : fromcode1;

  /* call system iconv with names it appreciates */
  if ((cd = iconv_open (tocode2, fromcode2)) != (iconv_t) -1)
    return cd;
  
  return (iconv_t) -1;
}