void *
PeerDigest::operator new (size_t)
{
    CBDATA_INIT_TYPE(PeerDigest);
    PeerDigest *result = cbdataAlloc(PeerDigest);
    return result;
}