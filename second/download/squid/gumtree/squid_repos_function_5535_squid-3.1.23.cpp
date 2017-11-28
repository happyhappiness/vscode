void *
ESIStreamContext::operator new(size_t byteCount)
{
    assert (byteCount == sizeof (ESIStreamContext));
    CBDATA_INIT_TYPE(ESIStreamContext);
    ESIStreamContext *result = cbdataAlloc(ESIStreamContext);
    return result;
}