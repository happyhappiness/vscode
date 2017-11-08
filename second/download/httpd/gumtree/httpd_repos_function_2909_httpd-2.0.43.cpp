apr_status_t apr_threadkey_private_get(void **new, apr_threadkey_t *key)
{
    apr_status_t stat;
    
    if ((stat = NXKeyGetValue(key->key, new)) == 0) {
        return APR_SUCCESS;
    }
    else {
        return stat;    
    }
}