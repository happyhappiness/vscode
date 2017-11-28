char const *
ESIExpatParser::errorString() const
{
    return XML_ErrorString(XML_GetErrorCode(myParser()));
}