SBuf
Parser::Tokenizer::consume(const SBuf::size_type n)
{
    // careful: n may be npos!
    const SBuf result = buf_.consume(n);
    parsed_ += result.length();
    return result;
}