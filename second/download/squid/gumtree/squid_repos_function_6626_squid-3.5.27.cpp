bool
ESILibxml2Parser::parse(char const *dataToParse, size_t const lengthOfData, bool const endOfStream)
{
    return (xmlParseChunk(parser, dataToParse, lengthOfData, endOfStream) == 0);
}