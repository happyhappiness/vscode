int XMLCALL
XML_SetParamEntityParsing(XML_Parser parser,
                          enum XML_ParamEntityParsing peParsing)
{
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parsing)
    return 0;
#ifdef XML_DTD
  paramEntityParsing = peParsing;
  return 1;
#else
  return peParsing == XML_PARAM_ENTITY_PARSING_NEVER;
#endif
}