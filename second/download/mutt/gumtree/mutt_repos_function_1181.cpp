static size_t encode_block (char *s, char *d, size_t dlen,
			    const char *fromcode, const char *tocode,
			    encoder_t encoder)
{
  char buf1[ENCWORD_LEN_MAX - ENCWORD_LEN_MIN + 1];
  iconv_t cd;
  ICONV_CONST char *ib;
  char *ob;
  size_t ibl, obl, n1, n2;

  if (fromcode)
  {
    cd = mutt_iconv_open (tocode, fromcode, 0);
    assert (cd != (iconv_t)(-1));
    ib = d, ibl = dlen, ob = buf1, obl = sizeof (buf1) - strlen (tocode);
    n1 = iconv (cd, &ib, &ibl, &ob, &obl);
    n2 = iconv (cd, 0, 0, &ob, &obl);
    assert (n1 != (size_t)(-1) && n2 != (size_t)(-1));
    iconv_close (cd);
    return (*encoder) (s, buf1, ob - buf1, tocode);
  }
  else
    return (*encoder) (s, d, dlen, tocode);
}