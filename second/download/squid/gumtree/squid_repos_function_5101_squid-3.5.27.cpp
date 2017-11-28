SBuf::size_type
Parser::Tokenizer::skipAll(const CharacterSet &tokenChars)
{
    const SBuf::size_type prefixLen = buf_.findFirstNotOf(tokenChars);
    if (prefixLen == 0)
        return 0;
    return success(prefixLen);
}