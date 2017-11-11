ENCODING *
XmlInitUnknownEncodingNS(void *mem,
		         int *table,
		         int (*convert)(void *userData, const char *p),
		         void *userData)
{
  ENCODING *enc = XmlInitUnknownEncoding(mem, table, convert, userData);
  if (enc)
    ((struct normal_encoding *)enc)->type[ASCII_COLON] = BT_COLON;
  return enc;
}