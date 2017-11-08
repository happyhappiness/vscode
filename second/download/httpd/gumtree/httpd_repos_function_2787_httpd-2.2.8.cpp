int XML_SetParamEntityParsing(XML_Parser parser,
			      enum XML_ParamEntityParsing parsing)
{
#ifdef XML_DTD
  paramEntityParsing = parsing;
  return 1;
#else
  return parsing == XML_PARAM_ENTITY_PARSING_NEVER;
#endif
}