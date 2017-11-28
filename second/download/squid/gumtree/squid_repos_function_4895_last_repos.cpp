void
Http::One::Parser::clear()
{
    parsingStage_ = HTTP_PARSE_NONE;
    buf_ = NULL;
    msgProtocol_ = AnyP::ProtocolVersion();
    mimeHeaderBlock_.clear();
}