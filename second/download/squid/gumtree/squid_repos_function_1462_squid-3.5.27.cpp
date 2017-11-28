SBuf::size_type
SBuf::rfind(const SBuf &needle, SBuf::size_type endPos) const
{
    // when the needle is 1 char, use the 1-char rfind()
    if (needle.length() == 1)
        return rfind(needle[0], endPos);

    ++stats.find;

    // needle is bigger than haystack, impossible find
    if (length() < needle.length())
        return npos;

    // if startPos is npos, std::string scans from the end of hay
    if (endPos == npos || endPos > length()-needle.length())
        endPos = length()-needle.length();

    // an empty needle found at the end of the haystack
    if (needle.length() == 0)
        return endPos;

    char *bufBegin = buf();
    char *cur = bufBegin+endPos;
    const char needleBegin = needle[0];
    while (cur >= bufBegin) {
        if (*cur == needleBegin) {
            if (0 == memcmp(needle.buf(), cur, needle.length())) {
                // found
                return (cur-buf());
            }
        }
        --cur;
    }
    return npos;
}