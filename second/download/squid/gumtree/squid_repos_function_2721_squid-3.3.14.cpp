void *
TunnelStateData::operator new (size_t)
{
    CBDATA_INIT_TYPE(TunnelStateData);
    TunnelStateData *result = cbdataAlloc(TunnelStateData);
    return result;
}