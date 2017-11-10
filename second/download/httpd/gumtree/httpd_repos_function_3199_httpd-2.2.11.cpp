const ENCODING *NS(XmlGetUtf16InternalEncoding)(void)
{
#if XML_BYTE_ORDER == 12
  return &ns(internal_little2_encoding).enc;
#elif XML_BYTE_ORDER == 21
  return &ns(internal_big2_encoding).enc;
#else
  const short n = 1;
  return *(const char *)&n ? &ns(internal_little2_encoding).enc : &ns(internal_big2_encoding).enc;
#endif
}