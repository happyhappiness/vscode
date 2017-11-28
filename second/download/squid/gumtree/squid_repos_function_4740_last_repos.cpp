SBuf::size_type
SBuf::find(char c, size_type startPos) const
{
    ++stats.find;

    if (startPos == npos) // can't find anything if we look past end of SBuf
        return npos;

    // std::string returns npos if needle is outside hay
    if (startPos > length())
        return npos;

    const void *i = memchr(buf()+startPos, (int)c, (size_type)length()-startPos);

    if (i == NULL)
        return npos;

    return (static_cast<const char *>(i)-buf());
}