bool
ESIExpatParser::parse(char const *dataToParse, size_t const lengthOfData, bool const endOfStream)
{
    return XML_Parse(myParser(), dataToParse, lengthOfData, endOfStream);
}