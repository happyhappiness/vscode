static size_t try_block (ICONV_CONST char *d, size_t dlen,
			 const char *fromcode, const char *tocode,
			 encoder_t *encoder, size_t *wlen)
{
  char buf1[ENCWORD_LEN_MAX - ENCWORD_LEN_MIN + 1];
  iconv_t cd;
  ICONV_CONST char *ib;
  char *ob, *p;
  size_t ibl, obl;
  int count, len, len_b, len_q;

  if (fromcode)
  {
    cd = mutt_iconv_open (tocode, fromcode, 0);
    assert (cd != (iconv_t)(-1));
    ib = d, ibl = dlen, ob = buf1, obl = sizeof (buf1) - strlen (tocode);
    if (iconv (cd, &ib, &ibl, &ob, &obl) == (size_t)(-1) ||
	iconv (cd, 0, 0, &ob, &obl) == (size_t)(-1))
    {
      assert (errno == E2BIG);
      iconv_close (cd);
      assert (ib > d);
      return (ib - d == dlen) ? dlen : ib - d + 1;
    }
    iconv_close (cd);
  }
  else
  {
    if (dlen > sizeof (buf1) - strlen (tocode))
      return sizeof (buf1) - strlen (tocode) + 1;
    memcpy (buf1, d, dlen);
    ob = buf1 + dlen;
  }

  count = 0;
  for (p = buf1; p < ob; p++)
  {
    unsigned char c = *p;
    assert (strchr (MimeSpecials, '?'));
    if (c >= 0x7f || c < 0x20 || *p == '_' ||
	(c != ' ' && strchr (MimeSpecials, *p)))
      ++count;
  }

  len = ENCWORD_LEN_MIN - 2 + strlen (tocode);
  len_b = len + (((ob - buf1) + 2) / 3) * 4;
  len_q = len + (ob - buf1) + 2 * count;

  /* Apparently RFC 1468 says to use B encoding for iso-2022-jp. */
  if (!ascii_strcasecmp (tocode, "ISO-2022-JP"))
    len_q = ENCWORD_LEN_MAX + 1;

  if (len_b < len_q && len_b <= ENCWORD_LEN_MAX)
  {
    *encoder = b_encoder;
    *wlen = len_b;
    return 0;
  }
  else if (len_q <= ENCWORD_LEN_MAX)
  {
    *encoder = q_encoder;
    *wlen = len_q;
    return 0;
  }
  else
    return dlen;
}