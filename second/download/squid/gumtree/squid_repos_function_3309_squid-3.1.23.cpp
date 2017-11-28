void *
clientReplyContext::operator new (size_t byteCount)
{
    /* derived classes with different sizes must implement their own new */
    assert (byteCount == sizeof (clientReplyContext));
    CBDATA_INIT_TYPE(clientReplyContext);
    return cbdataAlloc(clientReplyContext);
}