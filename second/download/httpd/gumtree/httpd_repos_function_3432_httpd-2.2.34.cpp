static apr_status_t apr_ldap_pool_cleanup_set_null(void *data_)
{
    void **ptr = (void **)data_;
    *ptr = NULL;
    return APR_SUCCESS;
}