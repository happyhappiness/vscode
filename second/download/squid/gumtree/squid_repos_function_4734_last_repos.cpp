const char*
SBuf::rawContent() const
{
    ++stats.rawAccess;
    return buf();
}