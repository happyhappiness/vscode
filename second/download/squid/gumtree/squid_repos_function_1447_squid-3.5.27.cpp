int
SBuf::compare(const char *s, const SBufCaseSensitive isCaseSensitive, const size_type n) const
{
    // 0-length comparison is always true regardless of buffer states
    if (!n) {
        ++stats.compareFast;
        return 0;
    }

    // N-length compare MUST provide a non-NULL C-string pointer
    assert(s);

    // when this is a 0-length string, no need for any complexity.
    if (!length()) {
        ++stats.compareFast;
        return '\0' - *s;
    }

    // brute-force scan in order to avoid ever needing strlen() on a c-string.
    ++stats.compareSlow;
    const char *left = buf();
    const char *right = s;
    int rv = 0;
    // what area to scan.
    // n may be npos, but we treat that as a huge positive value
    size_type byteCount = min(length(), n);

    // loop until we find a difference, a '\0', or reach the end of area to scan
    if (isCaseSensitive == caseSensitive) {
        while ((rv = *left - *right++) == 0) {
            if (*left++ == '\0' || --byteCount == 0)
                break;
        }
    } else {
        while ((rv = tolower(*left) - tolower(*right++)) == 0) {
            if (*left++ == '\0' || --byteCount == 0)
                break;
        }
    }

    // If we stopped scanning because we reached the end
    //  of buf() before we reached the end of s,
    // pretend we have a 0-terminator there to compare.
    // NP: the loop already incremented "right" ready for this comparison
    if (!byteCount && length() < n)
        return '\0' - *right;

    // If we found a difference within the scan area,
    // or we found a '\0',
    // or all n characters were identical (and none was \0).
    return rv;
}