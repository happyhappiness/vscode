ESISegment *
ESISegment::tail()
{
    ESISegment::Pointer result = this;

    while (result->next.getRaw())
        result = result->next;

    return result.getRaw();
}