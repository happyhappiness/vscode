apr_status_t apr_threadkey_private_delete(apr_threadkey_t *key)
{
    apr_status_t stat;
    if ((stat = NXKeyDelete(key->key)) == 0) {
        return APR_SUCCESS; 
    }
    return stat;
}