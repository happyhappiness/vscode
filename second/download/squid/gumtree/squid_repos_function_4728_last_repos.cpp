bool
SBuf::startsWith(const SBuf &S, const SBufCaseSensitive isCaseSensitive) const
{
    debugs(24, 8, id << " startsWith " << S.id << ", caseSensitive: " <<
           isCaseSensitive);
    if (length() < S.length()) {
        debugs(24, 8, "no, too short");
        ++stats.compareFast;
        return false;
    }
    return (compare(S, isCaseSensitive, S.length()) == 0);
}