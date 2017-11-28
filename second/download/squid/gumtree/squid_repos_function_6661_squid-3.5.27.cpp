void *
ESIVarState::operator new(size_t byteCount)
{
    assert (byteCount == sizeof (ESIVarState));
    void *rv;
    CBDATA_INIT_TYPE_FREECB(ESIVarState, esiVarStateFree);
    rv = (void *)cbdataAlloc (ESIVarState);
    return rv;
}