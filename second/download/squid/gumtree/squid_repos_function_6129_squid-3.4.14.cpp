long int
ESIExpatParser::lineNumber() const
{
    return (long int)XML_GetCurrentLineNumber(myParser());
}