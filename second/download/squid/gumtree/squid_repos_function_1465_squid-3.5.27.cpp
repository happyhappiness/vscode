SBuf::size_type
SBuf::findFirstNotOf(const CharacterSet &set, size_type startPos) const
{
    ++stats.find;

    if (startPos == npos)
        return npos;

    if (startPos >= length())
        return npos;

    debugs(24, 7, "first not of characterset " << set.name << " in id " << id);
    char *cur = buf()+startPos;
    const char *end = bufEnd();
    while (cur < end) {
        if (!set[*cur])
            return cur-buf();
        ++cur;
    }
    debugs(24, 7, "not found");
    return npos;
}