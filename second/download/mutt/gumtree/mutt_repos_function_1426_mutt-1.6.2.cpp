static void fix_uid (char *uid)
{
  char *s, *d;
  iconv_t cd;

  for (s = d = uid; *s;)
  {
    if (*s == '\\' && *(s+1) == 'x' && isxdigit ((unsigned char) *(s+2)) && isxdigit ((unsigned char) *(s+3)))
    {
      *d++ = hexval (*(s+2)) << 4 | hexval (*(s+3));
      s += 4;
    }
    else
      *d++ = *s++;
  }
  *d = '\0';

  if (_chs && (cd = mutt_iconv_open (_chs, "utf-8", 0)) != (iconv_t)-1)
  {
    int n = s - uid + 1; /* chars available in original buffer */
    char *buf;
    ICONV_CONST char *ib;
    char *ob;
    size_t ibl, obl;

    buf = safe_malloc (n+1);
    ib = uid, ibl = d - uid + 1, ob = buf, obl = n;
    iconv (cd, &ib, &ibl, &ob, &obl);
    if (!ibl)
    {
      if (ob-buf < n)
      {
	memcpy (uid, buf, ob-buf);
	uid[ob-buf] = '\0';
      }
      else if (n >= 0 && ob-buf == n && (buf[n] = 0, strlen (buf) < (size_t)n))
	memcpy (uid, buf, n);
    }
    FREE (&buf);
    iconv_close (cd);
  }
}