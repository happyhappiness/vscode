SBuf::size_type
Parser::Tokenizer::skipAll(const CharacterSet &tokenChars)
{
    const SBuf::size_type prefixLen = buf_.findFirstNotOf(tokenChars);
    if (prefixLen == 0) {
        debugs(24, 8, "no match when trying to skipAll " << tokenChars.name);
        return 0;
    }
    debugs(24, 8, "skipping all in " << tokenChars.name << " len " << prefixLen);
    return success(prefixLen);
}