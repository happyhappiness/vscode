iconv_t mutt_iconv_open (const char *tocode, const char *fromcode, int flags)
{
  char tocode1[SHORT_STRING];
  char fromcode1[SHORT_STRING];
  char *tocode2, *fromcode2;
  char *tmp;

  iconv_t cd;
  
  mutt_canonical_charset (tocode1, sizeof (tocode1), tocode);

#ifdef M_ICONV_HOOK_TO
  /* Not used. */
  if ((flags & M_ICONV_HOOK_TO) && (tmp = mutt_charset_hook (tocode1)))
    mutt_canonical_charset (tocode1, sizeof (tocode1), tmp);
#endif

  mutt_canonical_charset (fromcode1, sizeof (fromcode1), fromcode);
  if ((flags & M_ICONV_HOOK_FROM) && (tmp = mutt_charset_hook (fromcode1)))
    mutt_canonical_charset (fromcode1, sizeof (fromcode1), tmp);

  if ((cd = iconv_open (tocode1, fromcode1)) != (iconv_t) -1)
    return cd;
  if ((tocode2 = mutt_iconv_hook (tocode1)) && (fromcode2 = mutt_iconv_hook (fromcode1)))
    return iconv_open (tocode2, fromcode2);
  
  return (iconv_t) -1;
}