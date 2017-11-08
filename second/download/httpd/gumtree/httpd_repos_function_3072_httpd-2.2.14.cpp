static
enum XML_Error contentProcessor(XML_Parser parser,
				const char *start,
				const char *end,
				const char **endPtr)
{
  return doContent(parser, 0, encoding, start, end, endPtr);
}