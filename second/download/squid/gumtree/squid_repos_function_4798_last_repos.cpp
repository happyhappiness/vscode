void
Parser::BinaryTokenizer::got(uint32_t value, uint64_t size, const char *description) const
{
    debugs(24, 7, context << description << '=' << value <<
           BinaryTokenizer_tail(size, parsed_ - size));
}