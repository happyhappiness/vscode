int
SBuf::compare(const SBuf &S, const SBufCaseSensitive isCaseSensitive, const size_type n) const
{
    if (n != npos)
        return substr(0,n).compare(S.substr(0,n),isCaseSensitive);

    const size_type byteCompareLen = min(S.length(), length());
    ++stats.compareSlow;
    int rv = 0;
    if (isCaseSensitive == caseSensitive) {
        rv = memcmp(buf(), S.buf(), byteCompareLen);
    } else {
        rv = memcasecmp(buf(), S.buf(), byteCompareLen);
    }
    if (rv != 0)
        return rv;
    if (length() == S.length())
        return 0;
    if (length() > S.length())
        return 1;
    return -1;
}