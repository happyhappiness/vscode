bool
Http::One::Tokenizer::quotedString(SBuf &returnedToken, const bool http1p0)
{
    checkpoint();

    if (!skip('"'))
        return false;

    return qdText(returnedToken, http1p0);
}