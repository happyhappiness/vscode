void
ESIExpatParser::End(void *data,const XML_Char *el)
{
    XML_Parser parser = static_cast<XML_Parser>(data);
    ESIExpatParser *me = (ESIExpatParser *)XML_GetUserData(parser);
    me->theClient->end (el);
}