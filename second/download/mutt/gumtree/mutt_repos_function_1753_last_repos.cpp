static mbchar_table *parse_mbchar_table (const char *s)
{
  mbchar_table *t;
  size_t slen, k;
  mbstate_t mbstate;
  char *d;

  t = safe_calloc (1, sizeof (mbchar_table));
  slen = mutt_strlen (s);
  if (!slen)
    return t;

  t->orig_str = safe_strdup (s);
  /* This could be more space efficient.  However, being used on tiny
   * strings (Tochars and StChars), the overhead is not great. */
  t->chars = safe_calloc (slen, sizeof (char *));
  d = t->segmented_str = safe_calloc (slen * 2, sizeof (char));

  memset (&mbstate, 0, sizeof (mbstate));
  while (slen && (k = mbrtowc (NULL, s, slen, &mbstate)))
  {
    if (k == (size_t)(-1) || k == (size_t)(-2))
    {
      dprint (1, (debugfile,
                  "parse_mbchar_table: mbrtowc returned %d converting %s in %s\n",
                  (k == (size_t)(-1)) ? -1 : -2,
                  s, t->orig_str));
      if (k == (size_t)(-1))
        memset (&mbstate, 0, sizeof (mbstate));
      k = (k == (size_t)(-1)) ? 1 : slen;
    }

    slen -= k;
    t->chars[t->len++] = d;
    while (k--)
      *d++ = *s++;
    *d++ = '\0';
  }

  return t;
}