static const XML_Char *poolCopyString(STRING_POOL *pool, const XML_Char *s)
{
  do {
    if (!poolAppendChar(pool, *s))
      return 0;
  } while (*s++);
  s = pool->start;
  poolFinish(pool);
  return s;
}