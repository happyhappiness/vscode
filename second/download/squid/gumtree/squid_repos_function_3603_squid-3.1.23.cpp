void *
UrnState::operator new (size_t byteCount)
{
    /* derived classes with different sizes must implement their own new */
    assert (byteCount == sizeof (UrnState));
    CBDATA_INIT_TYPE(UrnState);
    return cbdataAlloc(UrnState);

}