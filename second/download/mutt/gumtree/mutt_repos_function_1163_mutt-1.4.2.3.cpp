int rfc2231_encode_string (char **pd)
{
  int ext = 0, encode = 0;
  char *charset, *s, *t, *e, *d = 0;
  size_t slen, dlen = 0;

  /* 
   * A shortcut to detect pure 7bit data.
   * 
   * This should prevent the worst when character set handling
   * is flawed.
   */

  for (s = *pd; *s; s++)
    if (*s & 0x80)
      break;
  
  if (!*s)
    return 0;
  
  if (!Charset || !SendCharset ||
      !(charset = mutt_choose_charset (Charset, SendCharset,
				  *pd, strlen (*pd), &d, &dlen)))
  {
    charset = safe_strdup (Charset ? Charset : "unknown-8bit");
    d = *pd;
    dlen = strlen (d);
  }

  if (!mutt_is_us_ascii (charset))
    encode = 1;

  for (s = d, slen = dlen; slen; s++, slen--)
    if (*s < 0x20 || *s >= 0x7f)
      encode = 1, ++ext;
    else if (strchr (MimeSpecials, *s) || strchr ("*'%", *s))
      ++ext;

  if (encode)
  {
    e = safe_malloc (dlen + 2*ext + strlen (charset) + 3);
    sprintf (e, "%s''", charset);	/* __SPRINTF_CHECKED__ */
    t = e + strlen (e);
    for (s = d, slen = dlen; slen; s++, slen--)
      if (*s < 0x20 || *s >= 0x7f ||
	  strchr (MimeSpecials, *s) || strchr ("*'%", *s))
      {
	sprintf (t, "%%%02X", (unsigned char)*s);
	t += 3;
      }
      else
	*t++ = *s;
    *t = '\0';

    if (d != *pd)
      safe_free ((void **) &d);
    safe_free ((void **) pd);
    *pd = e;
  }
  else if (d != *pd)
  {
    safe_free ((void **) pd);
    *pd = d;
  }
  
  safe_free ((void **) &charset);
  
  return encode;
}