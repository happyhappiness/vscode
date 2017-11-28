bool
Parser::Tokenizer::skipSuffix(const SBuf &tokenToSkip)
{
    if (buf_.length() < tokenToSkip.length())
        return false;

    SBuf::size_type offset = 0;
    if (tokenToSkip.length() < buf_.length())
        offset = buf_.length() - tokenToSkip.length();

    if (buf_.substr(offset, SBuf::npos).cmp(tokenToSkip) == 0) {
        debugs(24, 8, "skipping " << tokenToSkip.length());
        return successTrailing(tokenToSkip.length());
    }
    return false;
}