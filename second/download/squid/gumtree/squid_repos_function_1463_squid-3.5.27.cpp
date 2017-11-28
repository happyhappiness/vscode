SBuf::size_type
SBuf::rfind(char c, SBuf::size_type endPos) const
{
    ++stats.find;

    // shortcut: haystack is empty, can't find anything by definition
    if (length() == 0)
        return npos;

    // on npos input std::string compares last octet of hay
    if (endPos == npos || endPos >= length()) {
        endPos = length();
    } else {
        // NP: off-by-one weirdness:
        // endPos is an offset ... 0-based
        // length() is a count ... 1-based
        // memrhr() requires a 1-based count of space to scan.
        ++endPos;
    }

    if (length() == 0)
        return endPos;

    const void *i = memrchr(buf(), (int)c, (size_type)endPos);

    if (i == NULL)
        return npos;

    return (static_cast<const char *>(i)-buf());
}