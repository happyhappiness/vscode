static
int unknown_isInvalid(const ENCODING *enc, const char *p)
{
  int c = ((const struct unknown_encoding *)enc)
	   ->convert(((const struct unknown_encoding *)enc)->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber(c) < 0;
}