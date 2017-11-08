static ELEMENT_TYPE *
getElementType(XML_Parser parser,
	       const ENCODING *enc,
	       const char *ptr,
	       const char *end)
{
  const XML_Char *name = poolStoreString(&dtd.pool, enc, ptr, end);
  ELEMENT_TYPE *ret;

  if (! name)
    return 0;
  ret = (ELEMENT_TYPE *) lookup(&dtd.elementTypes, name, sizeof(ELEMENT_TYPE));
  if (! ret)
    return 0;
  if (ret->name != name)
    poolDiscard(&dtd.pool);
  else {
    poolFinish(&dtd.pool);
    if (!setElementTypePrefix(parser, ret))
      return 0;
  }
  return ret;
}