apr_status_t apr_os_threadkey_get(apr_os_threadkey_t *thekey,
                                               apr_threadkey_t *key)
{
    thekey = &(key->key);
    return APR_SUCCESS;
}