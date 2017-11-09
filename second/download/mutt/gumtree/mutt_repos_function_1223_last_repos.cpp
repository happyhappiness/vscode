static size_t convert_string (ICONV_CONST char *f, size_t flen,
			      const char *from, const char *to,
			      char **t, size_t *tlen)
{
  iconv_t cd;
  char *buf, *ob;
  size_t obl, n;
  int e;

  cd = mutt_iconv_open (to, from, 0);
  if (cd == (iconv_t)(-1))
    return (size_t)(-1);
  obl = 4 * flen + 1;
  ob = buf = safe_malloc (obl);
  n = iconv (cd, &f, &flen, &ob, &obl);
  if (n == (size_t)(-1) || iconv (cd, 0, 0, &ob, &obl) == (size_t)(-1))
  {
    e = errno;
    FREE (&buf);
    iconv_close (cd);
    errno = e;
    return (size_t)(-1);
  }
  *ob = '\0';
  
  *tlen = ob - buf;

  safe_realloc (&buf, ob - buf + 1);
  *t = buf;
  iconv_close (cd);

  return n;
}