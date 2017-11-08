apr_status_t apr_threadkey_data_set(void *data,
                                 const char *key, apr_status_t (*cleanup) (void *),
                                 apr_threadkey_t *threadkey)
{
    return apr_pool_userdata_set(data, key, cleanup, threadkey->pool);
}