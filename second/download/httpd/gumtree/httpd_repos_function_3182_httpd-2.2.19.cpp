static int PTRFASTCALL
utf8_isInvalid2(const ENCODING *enc, const char *p)
{
  return UTF8_INVALID2((const unsigned char *)p);
}