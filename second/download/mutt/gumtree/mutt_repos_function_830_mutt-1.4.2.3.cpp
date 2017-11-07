char *mutt_quote_string (const char *s)
{
  char *r, *pr;
  size_t rlen;

  rlen = mutt_strlen (s) + 3;
  pr = r = (char *) safe_malloc (rlen);
  *pr++ = '"';
  while (*s)
  {
    if (INVALID_CHAR (*s))
    {
      size_t o = pr - r;
      safe_realloc ((void **) &r, ++rlen);
      pr = r + o;
      *pr++ = '\\';
    }
    *pr++ = *s++;
  }
  *pr++ = '"';
  *pr = 0;
  return (r);
}