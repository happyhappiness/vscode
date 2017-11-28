SBuf::size_type
SBuf::findLastNotOf(const CharacterSet &set, size_type endPos) const
{
    ++stats.find;

    if (isEmpty())
        return npos;

    if (endPos == npos || endPos >= length())
        endPos = length() - 1;

    debugs(24, 7, "last not of characterset " << set.name << " in id " << id);
    const char *start = buf();
    for (const char *cur = start + endPos; cur >= start; --cur) {
        if (!set[*cur])
            return cur - start;
    }
    debugs(24, 7, "not found");
    return npos;
}