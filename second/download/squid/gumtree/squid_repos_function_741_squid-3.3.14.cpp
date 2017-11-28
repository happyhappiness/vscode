void *
ClientHttpRequest::operator new (size_t size)
{
    assert (size == sizeof (ClientHttpRequest));
    CBDATA_INIT_TYPE(ClientHttpRequest);
    ClientHttpRequest *result = cbdataAlloc(ClientHttpRequest);
    return result;
}