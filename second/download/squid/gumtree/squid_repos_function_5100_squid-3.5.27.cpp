bool
Parser::Tokenizer::prefix(SBuf &returnedToken, const CharacterSet &tokenChars, const SBuf::size_type limit)
{
    SBuf::size_type prefixLen = buf_.substr(0,limit).findFirstNotOf(tokenChars);
    if (prefixLen == 0)
        return false;
    if (prefixLen == SBuf::npos && (atEnd() || limit == 0))
        return false;
    if (prefixLen == SBuf::npos && limit > 0)
        prefixLen = limit;
    returnedToken = consume(prefixLen); // cannot be empty after the npos check
    return true;
}