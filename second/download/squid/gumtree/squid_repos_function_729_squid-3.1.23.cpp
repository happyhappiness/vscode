void *
ClientRequestContext::operator new (size_t size)
{
    assert (size == sizeof(ClientRequestContext));
    CBDATA_INIT_TYPE(ClientRequestContext);
    ClientRequestContext *result = cbdataAlloc(ClientRequestContext);
    return result;
}