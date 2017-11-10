enum XML_Error XMLCALL
XML_UseForeignDTD(XML_Parser parser, XML_Bool useDTD)
{
#ifdef XML_DTD
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parsing)
    return XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING;
  useForeignDTD = useDTD;
  return XML_ERROR_NONE;
#else
  return XML_ERROR_FEATURE_REQUIRES_XML_DTD;
#endif
}