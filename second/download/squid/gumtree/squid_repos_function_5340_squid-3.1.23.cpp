void
ESIContext::ParserState::init(ESIParserClient *userData)
{
    theParser = ESIParser::NewParser (userData);
    inited_ = true;
}