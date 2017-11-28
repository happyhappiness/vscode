bool
Parser::Tokenizer::skip(const SBuf &tokenToSkip)
{
    if (buf_.startsWith(tokenToSkip)) {
        debugs(24, 8, "skipping " << tokenToSkip.length());
        return success(tokenToSkip.length());
    }
    debugs(24, 8, "no match, not skipping '" << tokenToSkip << '\'');
    return false;
}