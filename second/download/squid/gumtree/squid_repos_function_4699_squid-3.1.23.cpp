void *
UFSStoreState::operator new (size_t)
{
    CBDATA_INIT_TYPE(UFSStoreState);
    return cbdataAlloc(UFSStoreState);
}