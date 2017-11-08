static void *create_session_crypto_config(apr_pool_t * p, server_rec *s)
{
    session_crypto_conf *new =
    (session_crypto_conf *) apr_pcalloc(p, sizeof(session_crypto_conf));

    /* if no library has been configured, set the recommended library
     * as a sensible default.
     */
#ifdef APU_CRYPTO_RECOMMENDED_DRIVER
    new->library = APU_CRYPTO_RECOMMENDED_DRIVER;
#endif

    return (void *) new;
}