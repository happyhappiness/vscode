void *
acl_access::operator new (size_t)
{
    CBDATA_INIT_TYPE(acl_access);
    acl_access *result = cbdataAlloc(acl_access);
    return result;
}