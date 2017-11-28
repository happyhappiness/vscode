void
ESIExpatParser::Default(void *data, const XML_Char *s, int len)
{
    XML_Parser parser = static_cast<XML_Parser>(data);
    ESIExpatParser *me = (ESIExpatParser *)XML_GetUserData(parser);
    me->theClient->parserDefault (s, len);
}