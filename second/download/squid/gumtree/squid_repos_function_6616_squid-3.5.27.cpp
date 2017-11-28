ESISegment const *
ESISegment::tail() const
{
    ESISegment const *result = this;

    while (result->next.getRaw())
        result = result->next.getRaw();

    return result;
}