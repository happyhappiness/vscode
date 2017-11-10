static
int utf8_isNmstrt3(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING3(nmstrtPages, (const unsigned char *)p);
}