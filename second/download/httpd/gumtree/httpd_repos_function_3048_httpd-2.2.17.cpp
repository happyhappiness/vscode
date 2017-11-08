XML_Parser XMLCALL
XML_ParserCreate_MM(const XML_Char *encodingName,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *nameSep)
{
  XML_Parser parser = parserCreate(encodingName, memsuite, nameSep, NULL);
  if (parser != NULL && ns) {
    /* implicit context only set for root parser, since child
       parsers (i.e. external entity parsers) will inherit it
    */
    if (!setContext(parser, implicitContext)) {
      XML_ParserFree(parser);
      return NULL;
    }
  }
  return parser;
}