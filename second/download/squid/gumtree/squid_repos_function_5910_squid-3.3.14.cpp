void *
ESIContext::operator new(size_t byteCount)
{
    assert (byteCount == sizeof (ESIContext));
    CBDATA_INIT_TYPE(ESIContext);
    ESIContext *result = cbdataAlloc(ESIContext);
    return result;
}