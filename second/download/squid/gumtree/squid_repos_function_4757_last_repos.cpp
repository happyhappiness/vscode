inline String
SBufToString(const SBuf &s)
{
    String rv;
    rv.limitInit(s.rawContent(), s.length());
    return rv;
}