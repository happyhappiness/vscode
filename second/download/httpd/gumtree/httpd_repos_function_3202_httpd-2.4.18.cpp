static void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st =
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));

    /* Create a per vhost pool for mod_ldap to use, serialized with
     * st->mutex (also one per vhost).  both are replicated by fork(),
     * no shared memory managed by either.
     */
    apr_pool_create(&st->pool, p);
#if APR_HAS_THREADS
    apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);
#endif

    st->cache_bytes = 500000;
    st->search_cache_ttl = 600000000;
    st->search_cache_size = 1024;
    st->compare_cache_ttl = 600000000;
    st->compare_cache_size = 1024;
    st->connections = NULL;
    st->ssl_supported = 0;
    st->global_certs = apr_array_make(p, 10, sizeof(apr_ldap_opt_tls_cert_t));
    st->secure = APR_LDAP_NONE;
    st->secure_set = 0;
    st->connectionTimeout = 10;
    st->opTimeout = apr_pcalloc(p, sizeof(struct timeval));
    st->opTimeout->tv_sec = 60;
    st->verify_svr_cert = 1;
    st->connection_pool_ttl = AP_LDAP_CONNPOOL_DEFAULT; /* no limit */
    st->retries = 3;
    st->retry_delay = 0; /* no delay */

    return st;
}