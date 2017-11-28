long int
ESILibxml2Parser::lineNumber() const
{
    return (long int)xmlSAX2GetLineNumber(parser);
}