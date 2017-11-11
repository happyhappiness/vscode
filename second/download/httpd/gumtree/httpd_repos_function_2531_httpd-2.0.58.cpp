static
enum XML_Error externalEntityContentProcessor(XML_Parser parser,
					      const char *start,
					      const char *end,
					      const char **endPtr)
{
  return doContent(parser, 1, encoding, start, end, endPtr);
}