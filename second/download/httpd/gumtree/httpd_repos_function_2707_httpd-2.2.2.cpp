void XML_SetDefaultHandlerExpand(XML_Parser parser,
				 XML_DefaultHandler handler)
{
  defaultHandler = handler;
  defaultExpandInternalEntities = 1;
}