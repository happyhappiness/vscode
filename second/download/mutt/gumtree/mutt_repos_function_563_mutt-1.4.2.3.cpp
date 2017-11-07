size_t mutt_iconv (iconv_t cd, ICONV_CONST char **inbuf, size_t *inbytesleft,
		   char **outbuf, size_t *outbytesleft,
		   ICONV_CONST char **inrepls, const char *outrepl)
{
  size_t ret = 0, ret1;
  ICONV_CONST char *ib = *inbuf;
  size_t ibl = *inbytesleft;
  char *ob = *outbuf;
  size_t obl = *outbytesleft;

  for (;;)
  {
    ret1 = iconv (cd, &ib, &ibl, &ob, &obl);
    if (ret1 != (size_t)-1)
      ret += ret1;
    if (ibl && obl && errno == EILSEQ)
    {
      if (inrepls)
      {
	/* Try replacing the input */
	ICONV_CONST char **t;
	for (t = inrepls; *t; t++)
	{
	  ICONV_CONST char *ib1 = *t;
	  size_t ibl1 = strlen (*t);
	  char *ob1 = ob;
	  size_t obl1 = obl;
	  iconv (cd, &ib1, &ibl1, &ob1, &obl1);
	  if (!ibl1)
	  {
	    ++ib, --ibl;
	    ob = ob1, obl = obl1;
	    ++ret;
	    break;
	  }
	}
	if (*t)
	  continue;
      }
      if (outrepl)
      {
	/* Try replacing the output */
	int n = strlen (outrepl);
	if (n <= obl)
	{
	  memcpy (ob, outrepl, n);
	  ++ib, --ibl;
	  ob += n, obl -= n;
	  ++ret;
	  continue;
	}
      }
    }
    *inbuf = ib, *inbytesleft = ibl;
    *outbuf = ob, *outbytesleft = obl;
    return ret;
  }
}