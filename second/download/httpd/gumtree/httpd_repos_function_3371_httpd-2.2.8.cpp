apr_status_t apr_threadkey_data_get(void **data, const char *key, apr_threadkey_t *threadkey)
{
    return apr_pool_userdata_get(data, key, threadkey->pool);
}