static int PTRFASTCALL
utf8_isName3(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING3(namePages, (const unsigned char *)p);
}