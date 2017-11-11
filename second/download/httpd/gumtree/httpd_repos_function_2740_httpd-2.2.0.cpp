static
enum XML_Error cdataSectionProcessor(XML_Parser parser,
				     const char *start,
			    	     const char *end,
				     const char **endPtr)
{
  enum XML_Error result = doCdataSection(parser, encoding, &start, end, endPtr);
  if (start) {
    processor = contentProcessor;
    return contentProcessor(parser, start, end, endPtr);
  }
  return result;
}