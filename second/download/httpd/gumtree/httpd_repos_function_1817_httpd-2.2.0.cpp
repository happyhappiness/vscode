static void *util_ldap_merge_config(apr_pool_t *p, void *basev,
                                    void *overridesv)
{
    util_ldap_state_t *st = apr_pcalloc(p, sizeof(util_ldap_state_t));
    util_ldap_state_t *base = (util_ldap_state_t *) basev;
    util_ldap_state_t *overrides = (util_ldap_state_t *) overridesv;

    st->pool = p;

    st->cache_bytes = base->cache_bytes;
    st->search_cache_ttl = base->search_cache_ttl;
    st->search_cache_size = base->search_cache_size;
    st->compare_cache_ttl = base->compare_cache_ttl;
    st->compare_cache_size = base->compare_cache_size;
    st->connections = base->connections;
    st->ssl_supported = base->ssl_supported;
    st->global_certs = apr_array_append(p, base->global_certs,
                                           overrides->global_certs);
    st->client_certs = apr_array_append(p, base->client_certs,
                                           overrides->client_certs);
    st->secure = (overrides->secure_set == 0) ? base->secure
                                              : overrides->secure;

    return st;
}