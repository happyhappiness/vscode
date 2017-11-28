inline SBuf
StringToSBuf(const String &s)
{
    return SBuf(s.rawBuf(), s.size());
}