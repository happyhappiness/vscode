size_t mbrtowc_iconv (wchar_t *pwc, const char *s, size_t n,
		      mbstate_t *ps, iconv_t cd)
{
  static mbstate_t mbstate;
  ICONV_CONST char *ib, *ibmax;
  char *ob, *t;
  size_t ibl, obl, k, r;
  char bufi[8], bufo[6];

  if (!n)
    return (size_t)(-2);

  t = memchr (ps, 0, sizeof (*ps));
  k = t ? (t - (char *)ps) : sizeof (*ps);
  if (k > sizeof (bufi))
    k = 0;
  if (k)
  {
    /* use the buffer for input */
    memcpy (bufi, ps, k);
    ib = bufi;
    ibmax = bufi + (k + n < sizeof (bufi) ? k + n : sizeof (bufi));
    memcpy (bufi + k, s, ibmax - bufi - k);
  }
  else
  {
    /* use the real input */
    ib = (ICONV_CONST char*) s;
    ibmax = (ICONV_CONST char*) s + n;
  }

  ob = bufo;
  obl = sizeof (bufo);
  ibl = 1;

  for (;;)
  {
    r = iconv (cd, &ib, &ibl, &ob, &obl);
    if (ob > bufo && (!k || ib > bufi + k))
    {
      /* we have a character */
      memset (ps, 0, sizeof (*ps));
      utf8rtowc (pwc, bufo, ob - bufo, &mbstate);
      return (pwc && *pwc) ? (ib - (k ? bufi + k : s)) : 0;
    }
    else if (!r || (r == (size_t)(-1) && errno == EINVAL))
    {
      if (ib + ibl < ibmax)
	/* try using more input */
	++ibl;
      else if (k && ib > bufi + k && bufi + k + n > ibmax)
      {
	/* switch to using real input */
	ib = (ICONV_CONST char*) s + (ib - bufi - k);
	ibmax = (ICONV_CONST char*) s + n;
	k = 0;
	++ibl;
      }
      else
      {
	/* save the state and give up */
	memset (ps, 0, sizeof (*ps));
	if (ibl <= sizeof (mbstate_t)) /* need extra condition here! */
	  memcpy (ps, ib, ibl);
	return (size_t)(-2);
      }
    }
    else
    {
      /* bad input */
      errno = EILSEQ;
      return (size_t)(-1);
    }
  }
}