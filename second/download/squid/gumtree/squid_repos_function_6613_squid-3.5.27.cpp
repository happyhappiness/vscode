ESISegment::Pointer
ESISegment::cloneList () const
{
    ESISegment::Pointer result = new ESISegment (*this);
    result->next = next.getRaw() ? next->cloneList() : NULL;
    return result;
}