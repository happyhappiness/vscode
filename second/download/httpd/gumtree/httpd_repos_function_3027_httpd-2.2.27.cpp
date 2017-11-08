static apr_status_t crypto_clear(void *ptr)
{
    apr_crypto_clear_t *clear = (apr_crypto_clear_t *)ptr;

    memset(clear->buffer, 0, clear->size);
    clear->buffer = NULL;
    clear->size = 0;

    return APR_SUCCESS;
}