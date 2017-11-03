int mutt_convert_string (char **ps, const char *from, const char *to, int flags)
{
  iconv_t cd;
  ICONV_CONST char *repls[] = { "\357\277\275", "?", 0 };
  char *s = *ps;

  if (!s || !*s)
    return 0;

  if (to && from && (cd = mutt_iconv_open (to, from, flags)) != (iconv_t)-1)
  {
    int len;
    ICONV_CONST char *ib;
    char *buf, *ob;
    size_t ibl, obl;
    ICONV_CONST char **inrepls = 0;
    char *outrepl = 0;

    if (mutt_is_utf8 (to))
      outrepl = "\357\277\275";
    else if (mutt_is_utf8 (from))
      inrepls = repls;
    else
      outrepl = "?";
      
    len = strlen (s);
    ib = s, ibl = len + 1;
    obl = MB_LEN_MAX * ibl;
    ob = buf = safe_malloc (obl + 1);
    
    mutt_iconv (cd, &ib, &ibl, &ob, &obl, inrepls, outrepl);
    iconv_close (cd);

    *ob = '\0';

    FREE (ps);		/* __FREE_CHECKED__ */
    *ps = buf;
    
    mutt_str_adjust (ps);
    return 0;
  }
  else
    return -1;
}