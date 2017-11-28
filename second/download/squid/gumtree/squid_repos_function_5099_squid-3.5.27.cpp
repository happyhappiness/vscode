bool
Parser::Tokenizer::token(SBuf &returnedToken, const CharacterSet &delimiters)
{
    const Tokenizer saved(*this);
    skipAll(delimiters);
    const SBuf::size_type tokenLen = buf_.findFirstOf(delimiters); // not found = npos => consume to end
    if (tokenLen == SBuf::npos) {
        *this = saved;
        return false;
    }
    returnedToken = consume(tokenLen); // cannot be empty
    skipAll(delimiters);
    return true;
}