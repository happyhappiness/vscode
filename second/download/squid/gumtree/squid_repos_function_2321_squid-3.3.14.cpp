void *
store_client::operator new (size_t)
{
    CBDATA_INIT_TYPE(store_client);
    store_client *result = cbdataAlloc(store_client);
    return result;
}