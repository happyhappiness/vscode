static enum XML_Error PTRCALL
externalEntityContentProcessor(XML_Parser parser,
                               const char *start,
                               const char *end,
                               const char **endPtr)
{
  enum XML_Error result =
    doContent(parser, 1, encoding, start, end, endPtr);
  if (result != XML_ERROR_NONE)
    return result;
  if (!storeRawNames(parser))
    return XML_ERROR_NO_MEMORY;
  return result;
}