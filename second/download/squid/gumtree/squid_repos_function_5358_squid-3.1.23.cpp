void *
esiRemove::operator new(size_t byteCount)
{
    assert (byteCount == sizeof (esiRemove));
    void *rv;
    CBDATA_INIT_TYPE_FREECB(esiRemove, esiRemoveFree);
    rv = (void *)cbdataAlloc (esiRemove);
    return rv;
}