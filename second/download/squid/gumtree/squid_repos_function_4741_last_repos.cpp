SBuf::size_type
SBuf::find(const SBuf &needle, size_type startPos) const
{
    if (startPos == npos) { // can't find anything if we look past end of SBuf
        ++stats.find;
        return npos;
    }

    // std::string allows needle to overhang hay but not start outside
    if (startPos > length()) {
        ++stats.find;
        return npos;
    }

    // for empty needle std::string returns startPos
    if (needle.length() == 0) {
        ++stats.find;
        return startPos;
    }

    // if needle length is 1 use the char search
    if (needle.length() == 1)
        return find(needle[0], startPos);

    ++stats.find;

    char *start = buf()+startPos;
    char *lastPossible = buf()+length()-needle.length()+1;
    char needleBegin = needle[0];

    debugs(24, 7, "looking for " << needle << "starting at " << startPos <<
           " in id " << id);
    while (start < lastPossible) {
        char *tmp;
        debugs(24, 8, " begin=" << (void *) start <<
               ", lastPossible=" << (void*) lastPossible );
        tmp = static_cast<char *>(memchr(start, needleBegin, lastPossible-start));
        if (tmp == NULL) {
            debugs(24, 8 , "First byte not found");
            return npos;
        }
        // lastPossible guarrantees no out-of-bounds with memcmp()
        if (0 == memcmp(needle.buf(), tmp, needle.length())) {
            debugs(24, 8, "Found at " << (tmp-buf()));
            return (tmp-buf());
        }
        start = tmp+1;
    }
    debugs(24, 8, "not found");
    return npos;
}