static void *util_ldap_merge_config(apr_pool_t *p, void *basev,
                                    void *overridesv)
{
    util_ldap_state_t *st = apr_pcalloc(p, sizeof(util_ldap_state_t));
    util_ldap_state_t *base = (util_ldap_state_t *) basev;
    util_ldap_state_t *overrides = (util_ldap_state_t *) overridesv;

    st->pool = overrides->pool;
#if APR_HAS_THREADS
    st->mutex = overrides->mutex;
#endif

    /* The cache settings can not be modified in a 
        virtual host since all server use the same
        shared memory cache. */
    st->cache_bytes = base->cache_bytes;
    st->search_cache_ttl = base->search_cache_ttl;
    st->search_cache_size = base->search_cache_size;
    st->compare_cache_ttl = base->compare_cache_ttl;
    st->compare_cache_size = base->compare_cache_size;
    st->util_ldap_cache_lock = base->util_ldap_cache_lock; 

    st->connections = NULL;
    st->ssl_supported = 0;
    st->global_certs = apr_array_append(p, base->global_certs,
                                           overrides->global_certs);
    st->client_certs = apr_array_append(p, base->client_certs,
                                           overrides->client_certs);
    st->secure = (overrides->secure_set == 0) ? base->secure
                                              : overrides->secure;

    /* These LDAP connection settings can not be overwritten in 
        a virtual host. Once set in the base server, they must 
        remain the same. None of the LDAP SDKs seem to be able
        to handle setting the verify_svr_cert flag on a 
        per-connection basis.  The OpenLDAP client appears to be
        able to handle the connection timeout per-connection
        but the Novell SDK cannot.  Allowing the timeout to
        be set by each vhost is of little value so rather than
        trying to make special expections for one LDAP SDK, GLOBAL_ONLY 
        is being enforced on this setting as well. */
    st->connectionTimeout = base->connectionTimeout;
    st->verify_svr_cert = base->verify_svr_cert;

    return st;
}