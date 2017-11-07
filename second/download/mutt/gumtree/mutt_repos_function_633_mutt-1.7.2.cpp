int mutt_check_alias_name (const char *s, char *dest, size_t destlen)
{
  wchar_t wc;
  mbstate_t mb;
  size_t l;
  int rv = 0, bad = 0, dry = !dest || !destlen;

  memset (&mb, 0, sizeof (mbstate_t));

  if (!dry)
    destlen--;
  for (; s && *s && (dry || destlen) &&
       (l = mbrtowc (&wc, s, MB_CUR_MAX, &mb)) != 0;
       s += l, destlen -= l)
  {
    bad = l == (size_t)(-1) || l == (size_t)(-2); /* conversion error */
    bad = bad || (!dry && l > destlen);		/* too few room for mb char */
    if (l == 1)
      bad = bad || (strchr ("-_+=.", *s) == NULL && !iswalnum (wc));
    else
      bad = bad || !iswalnum (wc);
    if (bad)
    {
      if (dry)
	return -1;
      if (l == (size_t)(-1))
        memset (&mb, 0, sizeof (mbstate_t));
      *dest++ = '_';
      rv = -1;
    }
    else if (!dry)
    {
      memcpy (dest, s, l);
      dest += l;
    }
  }
  if (!dry)
    *dest = 0;
  return rv;
}