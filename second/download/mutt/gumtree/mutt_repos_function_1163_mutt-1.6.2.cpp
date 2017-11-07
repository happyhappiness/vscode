void _rfc2047_encode_string (char **pd, int encode_specials, int col)
{
  char *e;
  size_t elen;
  char *charsets;

  if (!Charset || !*pd)
    return;

  charsets = SendCharset;
  if (!charsets || !*charsets)
    charsets = "utf-8";

  rfc2047_encode (*pd, strlen (*pd), col,
		  Charset, charsets, &e, &elen,
		  encode_specials ? RFC822Specials : NULL);

  FREE (pd);		/* __FREE_CHECKED__ */
  *pd = e;
}