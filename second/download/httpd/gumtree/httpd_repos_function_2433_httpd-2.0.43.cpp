void XML_SetExternalEntityRefHandlerArg(XML_Parser parser, void *arg)
{
  if (arg)
    externalEntityRefHandlerArg = arg;
  else
    externalEntityRefHandlerArg = parser;
}