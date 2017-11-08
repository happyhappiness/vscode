static int PTRFASTCALL
unknown_isNmstrt(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = AS_UNKNOWN_ENCODING(enc);
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING(nmstrtPages, c >> 8, c & 0xFF);
}