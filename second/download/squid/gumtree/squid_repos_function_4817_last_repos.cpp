SBuf
Parser::Tokenizer::consumeTrailing(const SBuf::size_type n)
{
    debugs(24, 5, "consuming " << n << " bytes");

    // If n is npos, we consume everything from buf_ (and nothing from result).
    const SBuf::size_type parsed = (n == SBuf::npos) ? buf_.length() : n;

    SBuf result = buf_;
    buf_ = result.consume(buf_.length() - parsed);
    parsed_ += parsed;
    return result;
}