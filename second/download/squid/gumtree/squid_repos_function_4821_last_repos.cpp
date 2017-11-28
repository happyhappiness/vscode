bool
Parser::Tokenizer::suffix(SBuf &returnedToken, const CharacterSet &tokenChars, const SBuf::size_type limit)
{
    SBuf span = buf_;

    if (limit < buf_.length())
        span.consume(buf_.length() - limit); // ignore the N prefix characters

    auto i = span.rbegin();
    SBuf::size_type found = 0;
    while (i != span.rend() && tokenChars[*i]) {
        ++i;
        ++found;
    }
    if (!found)
        return false;
    returnedToken = consumeTrailing(found);
    return true;
}