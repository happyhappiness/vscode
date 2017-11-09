static int rfc2047_encode (ICONV_CONST char *d, size_t dlen, int col,
			   const char *fromcode, const char *charsets,
			   char **e, size_t *elen, char *specials)
{
  int ret = 0;
  char *buf;
  size_t bufpos, buflen;
  char *u = NULL, *t0, *t1, *t;
  char *s0, *s1;
  size_t ulen, r, n, wlen;
  encoder_t encoder;
  char *tocode1 = 0;
  const char *tocode;
  char *icode = "utf-8";

  /* Try to convert to UTF-8. */
  if (convert_string (d, dlen, fromcode, icode, &u, &ulen))
  {
    ret = 1; 
    icode = 0;
    safe_realloc (&u, (ulen = dlen) + 1);
    memcpy (u, d, dlen);
    u[ulen] = 0;
  }

  /* Find earliest and latest things we must encode. */
  s0 = s1 = t0 = t1 = 0;
  for (t = u; t < u + ulen; t++)
  {
    if ((*t & 0x80) || 
	(*t == '=' && t[1] == '?' && (t == u || HSPACE(*(t-1)))))
    {
      if (!t0) t0 = t;
      t1 = t;
    }
    else if (specials && *t && strchr (specials, *t))
    {
      if (!s0) s0 = t;
      s1 = t;
    }
  }

  /* If we have something to encode, include RFC822 specials */
  if (t0 && s0 && s0 < t0)
    t0 = s0;
  if (t1 && s1 && s1 > t1)
    t1 = s1;

  if (!t0)
  {
    /* No encoding is required. */
    *e = u;
    *elen = ulen;
    return ret;
  }

  /* Choose target charset. */
  tocode = fromcode;
  if (icode)
  {
    if ((tocode1 = mutt_choose_charset (icode, charsets, u, ulen, 0, 0)))
      tocode = tocode1;
    else
      ret = 2, icode = 0;
  }

  /* Hack to avoid labelling 8-bit data as us-ascii. */
  if (!icode && mutt_is_us_ascii (tocode))
    tocode = "unknown-8bit";
  
  /* Adjust t0 for maximum length of line. */
  t = u + (ENCWORD_LEN_MAX + 1) - col - ENCWORD_LEN_MIN;
  if (t < u)  t = u;
  if (t < t0) t0 = t;
  

  /* Adjust t0 until we can encode a character after a space. */
  for (; t0 > u; t0--)
  {
    if (!HSPACE(*(t0-1)))
      continue;
    t = t0 + 1;
    if (icode)
      while (t < u + ulen && CONTINUATION_BYTE(*t))
	++t;
    if (!try_block (t0, t - t0, icode, tocode, &encoder, &wlen) &&
	col + (t0 - u) + wlen <= ENCWORD_LEN_MAX + 1)
      break;
  }

  /* Adjust t1 until we can encode a character before a space. */
  for (; t1 < u + ulen; t1++)
  {
    if (!HSPACE(*t1))
      continue;
    t = t1 - 1;
    if (icode)
      while (CONTINUATION_BYTE(*t))
	--t;
    if (!try_block (t, t1 - t, icode, tocode, &encoder, &wlen) &&
	1 + wlen + (u + ulen - t1) <= ENCWORD_LEN_MAX + 1)
      break;
  }

  /* We shall encode the region [t0,t1). */

  /* Initialise the output buffer with the us-ascii prefix. */
  buflen = 2 * ulen;
  buf = safe_malloc (buflen);
  bufpos = t0 - u;
  memcpy (buf, u, t0 - u);

  col += t0 - u;

  t = t0;
  for (;;)
  {
    /* Find how much we can encode. */
    n = choose_block (t, t1 - t, col, icode, tocode, &encoder, &wlen);
    if (n == t1 - t)
    {
      /* See if we can fit the us-ascii suffix, too. */
      if (col + wlen + (u + ulen - t1) <= ENCWORD_LEN_MAX + 1)
	break;
      n = t1 - t - 1;
      if (icode)
	while (CONTINUATION_BYTE(t[n]))
	  --n;
      assert (t + n >= t);
      if (!n)
      {
	/* This should only happen in the really stupid case where the
	   only word that needs encoding is one character long, but
	   there is too much us-ascii stuff after it to use a single
	   encoded word. We add the next word to the encoded region
	   and try again. */
	assert (t1 < u + ulen);
	for (t1++; t1 < u + ulen && !HSPACE(*t1); t1++)
	  ;
	continue;
      }
      n = choose_block (t, n, col, icode, tocode, &encoder, &wlen);
    }

    /* Add to output buffer. */
#define LINEBREAK "\n\t"
    if (bufpos + wlen + strlen (LINEBREAK) > buflen)
    {
      buflen = bufpos + wlen + strlen (LINEBREAK);
      safe_realloc (&buf, buflen);
    }
    r = encode_block (buf + bufpos, t, n, icode, tocode, encoder);
    assert (r == wlen);
    bufpos += wlen;
    memcpy (buf + bufpos, LINEBREAK, strlen (LINEBREAK));
    bufpos += strlen (LINEBREAK);
#undef LINEBREAK

    col = 1;

    t += n;
  }

  /* Add last encoded word and us-ascii suffix to buffer. */
  buflen = bufpos + wlen + (u + ulen - t1);
  safe_realloc (&buf, buflen + 1);
  r = encode_block (buf + bufpos, t, t1 - t, icode, tocode, encoder);
  assert (r == wlen);
  bufpos += wlen;
  memcpy (buf + bufpos, t1, u + ulen - t1);

  FREE (&tocode1);
  FREE (&u);

  buf[buflen] = '\0';
  
  *e = buf;
  *elen = buflen + 1;
  return ret;
}