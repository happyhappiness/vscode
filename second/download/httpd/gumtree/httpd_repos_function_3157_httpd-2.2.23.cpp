static enum XML_Error PTRCALL
contentProcessor(XML_Parser parser,
                 const char *start,
                 const char *end,
                 const char **endPtr)
{
  enum XML_Error result =
    doContent(parser, 0, encoding, start, end, endPtr);
  if (result != XML_ERROR_NONE)
    return result;
  if (!storeRawNames(parser))
    return XML_ERROR_NO_MEMORY;
  return result;
}