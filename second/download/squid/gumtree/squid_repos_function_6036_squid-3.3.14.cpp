void
ESIExpatParser::Start(void *data,const XML_Char *el, const char **attr)
{
    XML_Parser parser = static_cast<XML_Parser>(data);
    ESIExpatParser *me = (ESIExpatParser *)XML_GetUserData(parser);
    me->theClient->start (el, attr, XML_GetSpecifiedAttributeCount (parser));
}