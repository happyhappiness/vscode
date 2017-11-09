void ssl_util_thread_id_setup(apr_pool_t *p)
{
#if OPENSSL_VERSION_NUMBER >= 0x10000000L
    CRYPTO_THREADID_set_callback(ssl_util_thr_id);
#else
    CRYPTO_set_id_callback(ssl_util_thr_id);
#endif
    apr_pool_cleanup_register(p, NULL, ssl_util_thr_id_cleanup,
                                       apr_pool_cleanup_null);
}