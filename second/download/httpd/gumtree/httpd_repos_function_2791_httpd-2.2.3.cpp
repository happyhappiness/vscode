static
const XML_Char *poolAppendString(STRING_POOL *pool, const XML_Char *s)
{
  while (*s) {
    if (!poolAppendChar(pool, *s))
      return 0;
    s++;
  } 
  return pool->start;
}