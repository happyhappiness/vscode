void XML_SetDefaultHandler(XML_Parser parser,
			   XML_DefaultHandler handler)
{
  defaultHandler = handler;
  defaultExpandInternalEntities = 0;
}