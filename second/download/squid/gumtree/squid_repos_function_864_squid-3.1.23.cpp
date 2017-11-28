void *
ConnectStateData::operator new (size_t size)
{
    CBDATA_INIT_TYPE(ConnectStateData);
    return cbdataAlloc(ConnectStateData);
}