String
SBuf::toString() const
{
    String rv;
    rv.limitInit(buf(), length());
    ++stats.copyOut;
    return rv;
}