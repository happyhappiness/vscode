void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));

    st->pool = p;

    st->cache_bytes = 100000;
    st->search_cache_ttl = 600000000;
    st->search_cache_size = 1024;
    st->compare_cache_ttl = 600000000;
    st->compare_cache_size = 1024;
    st->connections = NULL;
    st->cert_auth_file = NULL;
    st->cert_file_type = LDAP_CA_TYPE_UNKNOWN;
    st->ssl_support = 0;
    st->connectionTimeout = 10;

    return st;
}