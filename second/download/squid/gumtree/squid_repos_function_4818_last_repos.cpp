SBuf::size_type
Parser::Tokenizer::successTrailing(const SBuf::size_type n)
{
    return consumeTrailing(n).length();
}