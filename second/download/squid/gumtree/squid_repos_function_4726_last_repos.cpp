int
SBuf::compare(const SBuf &S, const SBufCaseSensitive isCaseSensitive, const size_type n) const
{
    if (n != npos) {
        debugs(24, 8, "length specified. substr and recurse");
        return substr(0,n).compare(S.substr(0,n),isCaseSensitive);
    }

    const size_type byteCompareLen = min(S.length(), length());
    ++stats.compareSlow;
    int rv = 0;
    debugs(24, 8, "comparing length " << byteCompareLen);
    if (isCaseSensitive == caseSensitive) {
        rv = memcmp(buf(), S.buf(), byteCompareLen);
    } else {
        rv = memcasecmp(buf(), S.buf(), byteCompareLen);
    }
    if (rv != 0) {
        debugs(24, 8, "result: " << rv);
        return rv;
    }
    if (n <= length() || n <= S.length()) {
        debugs(24, 8, "same contents and bounded length. Equal");
        return 0;
    }
    if (length() == S.length()) {
        debugs(24, 8, "same contents and same length. Equal");
        return 0;
    }
    if (length() > S.length()) {
        debugs(24, 8, "lhs is longer than rhs. Result is 1");
        return 1;
    }
    debugs(24, 8, "rhs is longer than lhs. Result is -1");
    return -1;
}