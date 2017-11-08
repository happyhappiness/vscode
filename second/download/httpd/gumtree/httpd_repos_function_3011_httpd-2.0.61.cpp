apr_status_t apr_threadkey_private_set(void *priv, apr_threadkey_t *key)
{
    apr_status_t stat;
    if ((stat = NXKeySetValue(key->key, priv)) == 0) {
        return APR_SUCCESS;
    }
    else {
        return stat;
    }
}