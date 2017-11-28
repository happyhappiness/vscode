bool
Parser::Tokenizer::skip(const SBuf &tokenToSkip)
{
    if (buf_.startsWith(tokenToSkip))
        return success(tokenToSkip.length());
    return false;
}