void *
ESISegment::operator new(size_t byteCount)
{
    assert (byteCount == sizeof (ESISegment));
    void *rv;
    CBDATA_INIT_TYPE(ESISegment);
    rv = (void *)cbdataAlloc (ESISegment);
    return rv;
}