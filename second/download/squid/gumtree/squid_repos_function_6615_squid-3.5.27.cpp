size_t
ESISegment::append(ESISegment::Pointer from)
{
    return append (from->buf, from->len);
}