void
Parser::BinaryTokenizer::reset(const SBuf &data, const bool expectMore)
{
    *this = BinaryTokenizer(data, expectMore);
}