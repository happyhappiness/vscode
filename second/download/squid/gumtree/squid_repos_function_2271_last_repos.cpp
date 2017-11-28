bool
HttpHeader::hasNamed(const SBuf &s, String *result) const
{
    return hasNamed(s.rawContent(), s.length(), result);
}