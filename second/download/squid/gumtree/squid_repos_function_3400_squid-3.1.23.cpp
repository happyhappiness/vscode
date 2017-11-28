void *
ClientSocketContext::operator new (size_t byteCount)
{
    /* derived classes with different sizes must implement their own new */
    assert (byteCount == sizeof (ClientSocketContext));
    CBDATA_INIT_TYPE(ClientSocketContext);
    return cbdataAlloc(ClientSocketContext);
}