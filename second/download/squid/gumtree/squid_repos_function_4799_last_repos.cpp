void
Parser::BinaryTokenizer::got(const SBuf &value, uint64_t size, const char *description) const
{
    debugs(24, 7, context << description << '=' <<
           Raw(nullptr, value.rawContent(), value.length()).hex() <<
           BinaryTokenizer_tail(size, parsed_ - size));

}