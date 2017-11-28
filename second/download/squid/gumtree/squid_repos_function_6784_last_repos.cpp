size_t
ESISegment::append(char const *appendBuffer, size_t appendLength)
{
    size_t toCopy = min(appendLength, space());
    memcpy(&buf[len], appendBuffer, toCopy);
    len += toCopy;
    return toCopy;
}