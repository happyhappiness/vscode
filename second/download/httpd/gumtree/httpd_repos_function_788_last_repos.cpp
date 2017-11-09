static apr_status_t ssl_util_thr_id_cleanup(void *old)
{
    CRYPTO_THREADID_set_callback(old);
    return APR_SUCCESS;
}