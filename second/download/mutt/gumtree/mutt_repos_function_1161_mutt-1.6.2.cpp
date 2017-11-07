static size_t choose_block (char *d, size_t dlen, int col,
			    const char *fromcode, const char *tocode,
			    encoder_t *encoder, size_t *wlen)
{
  size_t n, nn;
  int utf8 = fromcode && !ascii_strcasecmp (fromcode, "utf-8");

  n = dlen;
  for (;;)
  {
    assert (d + n > d);
    nn = try_block (d, n, fromcode, tocode, encoder, wlen);
    if (!nn && (col + *wlen <= ENCWORD_LEN_MAX + 1 || n <= 1))
      break;
    n = (nn ? nn : n) - 1;
    assert (n > 0);
    if (utf8)
      while (n > 1 && CONTINUATION_BYTE(d[n]))
	--n;
  }
  return n;
}