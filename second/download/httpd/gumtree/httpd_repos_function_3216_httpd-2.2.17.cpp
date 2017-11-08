static int PTRFASTCALL
unknown_isInvalid(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = AS_UNKNOWN_ENCODING(enc);
  int c = uenc->convert(uenc->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber(c) < 0;
}