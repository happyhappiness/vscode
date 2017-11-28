SBuf::size_type
Parser::Tokenizer::success(const SBuf::size_type n)
{
    return consume(n).length();
}