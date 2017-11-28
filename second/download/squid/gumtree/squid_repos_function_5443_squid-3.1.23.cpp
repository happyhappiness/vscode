void
ESIExpatParser::Comment(void *data, const XML_Char *s)
{
    XML_Parser parser = static_cast<XML_Parser>(data);
    ESIExpatParser *me = (ESIExpatParser *)XML_GetUserData(parser);
    me->theClient->parserComment (s);
}