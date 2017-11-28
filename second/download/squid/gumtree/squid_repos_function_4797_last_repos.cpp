void
Parser::BinaryTokenizer::got(uint64_t size, const char *description) const
{
    debugs(24, 7, context << description <<
           BinaryTokenizer_tail(size, parsed_ - size));
}