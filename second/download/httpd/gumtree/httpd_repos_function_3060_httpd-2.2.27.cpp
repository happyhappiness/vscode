static apr_status_t crypto_cleanup(apr_crypto_t *f)
{
    apr_crypto_key_t *key;
    if (f->keys) {
        while ((key = apr_array_pop(f->keys))) {
            if (key->symKey) {
                PK11_FreeSymKey(key->symKey);
                key->symKey = NULL;
            }
        }
    }
    return APR_SUCCESS;
}