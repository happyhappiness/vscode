static
XML_Char *poolAppend(STRING_POOL *pool, const ENCODING *enc,
		     const char *ptr, const char *end)
{
  if (!pool->ptr && !poolGrow(pool))
    return 0;
  for (;;) {
    XmlConvert(enc, &ptr, end, (ICHAR **)&(pool->ptr), (ICHAR *)pool->end);
    if (ptr == end)
      break;
    if (!poolGrow(pool))
      return 0;
  }
  return pool->start;
}