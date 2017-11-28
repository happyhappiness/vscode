void
ESIContext::ParserState::freeResources()
{
    theParser = NULL;
    inited_ = false;
}