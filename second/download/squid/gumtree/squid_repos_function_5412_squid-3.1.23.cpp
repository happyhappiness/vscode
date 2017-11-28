void
ESISegment::ListAppend (ESISegment::Pointer &head, char const *s, size_t len)
{
    if (!head.getRaw())
        head = new ESISegment;

    head->tail()->listAppend (s, len);
}