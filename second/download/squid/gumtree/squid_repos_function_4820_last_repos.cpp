bool
Parser::Tokenizer::prefix(SBuf &returnedToken, const CharacterSet &tokenChars, const SBuf::size_type limit)
{
    SBuf::size_type prefixLen = buf_.substr(0,limit).findFirstNotOf(tokenChars);
    if (prefixLen == 0) {
        debugs(24, 8, "no prefix for set " << tokenChars.name);
        return false;
    }
    if (prefixLen == SBuf::npos && (atEnd() || limit == 0)) {
        debugs(24, 8, "no char in set " << tokenChars.name << " while looking for prefix");
        return false;
    }
    if (prefixLen == SBuf::npos && limit > 0) {
        debugs(24, 8, "whole haystack matched");
        prefixLen = limit;
    }
    debugs(24, 8, "found with length " << prefixLen);
    returnedToken = consume(prefixLen); // cannot be empty after the npos check
    return true;
}