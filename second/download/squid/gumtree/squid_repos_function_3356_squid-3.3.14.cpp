void *
ExternalACLEntry::operator new (size_t byteCount)
{
    /* derived classes with different sizes must implement their own new */
    assert (byteCount == sizeof (ExternalACLEntry));
    CBDATA_INIT_TYPE(ExternalACLEntry);
    return cbdataAlloc(ExternalACLEntry);
}