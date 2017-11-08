static apr_status_t apr_crypto_term(void *ptr)
{
    /* set drivers to NULL so init can work again */
    drivers = NULL;

    /* Everything else we need is handled by cleanups registered
     * when we created mutexes and loaded DSOs
     */
    return APR_SUCCESS;
}