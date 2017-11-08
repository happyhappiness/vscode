static
int unknown_isNmstrt(const ENCODING *enc, const char *p)
{
  int c = ((const struct unknown_encoding *)enc)
	  ->convert(((const struct unknown_encoding *)enc)->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING(nmstrtPages, c >> 8, c & 0xFF);
}