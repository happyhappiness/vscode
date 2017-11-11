static apr_status_t ssl_util_thread_cleanup(void *data)
{
    CRYPTO_set_locking_callback(NULL);
    CRYPTO_set_id_callback(NULL);

    /* Let the registered mutex cleanups do their own thing
     */
    return APR_SUCCESS;
}