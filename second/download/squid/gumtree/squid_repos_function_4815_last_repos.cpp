SBuf
Parser::Tokenizer::consume(const SBuf::size_type n)
{
    // careful: n may be npos!
    debugs(24, 5, "consuming " << n << " bytes");
    const SBuf result = buf_.consume(n);
    parsed_ += result.length();
    return result;
}