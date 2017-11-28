void
Parser::BinaryTokenizer::rollback()
{
    parsed_ = syncPoint_;
}