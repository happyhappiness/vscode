static size_t my_mbstowcs (wchar_t **pwbuf, size_t *pwbuflen, size_t i, char *buf)
{
  wchar_t wc;
  mbstate_t st;
  size_t k;
  wchar_t *wbuf;
  size_t wbuflen;

  wbuf = *pwbuf, wbuflen = *pwbuflen;
  
  while (*buf)
  {
    memset (&st, 0, sizeof (st));
    for (; (k = mbrtowc (&wc, buf, MB_LEN_MAX, &st)) &&
	 k != (size_t)(-1) && k != (size_t)(-2); buf += k)
    {
      if (i >= wbuflen)
      {
	wbuflen = i + 20;
	safe_realloc (&wbuf, wbuflen * sizeof (*wbuf));
      }
      wbuf[i++] = wc;
    }
    if (*buf && (k == (size_t) -1 || k == (size_t) -2))
    {
      if (i >= wbuflen) 
      {
	wbuflen = i + 20;
	safe_realloc (&wbuf, wbuflen * sizeof (*wbuf));
      }
      wbuf[i++] = replacement_char();
      buf++;
    }
  }
  *pwbuf = wbuf, *pwbuflen = wbuflen;
  return i;
}