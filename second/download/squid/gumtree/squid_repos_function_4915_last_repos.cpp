bool
Http::One::Tokenizer::quotedStringOrToken(SBuf &returnedToken, const bool http1p0)
{
    checkpoint();

    if (!skip('"'))
        return prefix(returnedToken, CharacterSet::TCHAR);

    return qdText(returnedToken, http1p0);
}