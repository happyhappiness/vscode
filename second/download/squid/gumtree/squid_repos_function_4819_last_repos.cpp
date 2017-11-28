bool
Parser::Tokenizer::token(SBuf &returnedToken, const CharacterSet &delimiters)
{
    const Tokenizer saved(*this);
    skipAll(delimiters);
    const SBuf::size_type tokenLen = buf_.findFirstOf(delimiters); // not found = npos => consume to end
    if (tokenLen == SBuf::npos) {
        debugs(24, 8, "no token found for delimiters " << delimiters.name);
        *this = saved;
        return false;
    }
    returnedToken = consume(tokenLen); // cannot be empty
    skipAll(delimiters);
    debugs(24, DBG_DATA, "token found for delimiters " << delimiters.name << ": '" <<
           returnedToken << '\'');
    return true;
}