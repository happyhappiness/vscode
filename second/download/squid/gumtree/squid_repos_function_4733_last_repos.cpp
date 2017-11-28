SBuf::size_type
SBuf::copy(char *dest, size_type n) const
{
    size_type toexport = min(n,length());
    memcpy(dest, buf(), toexport);
    ++stats.copyOut;
    return toexport;
}