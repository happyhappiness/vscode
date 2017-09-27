
    st->cache_bytes = 100000;
    st->search_cache_ttl = 600000000;
    st->search_cache_size = 1024;
    st->compare_cache_ttl = 600000000;
    st->compare_cache_size = 1024;

    st->connections = NULL;
#ifdef APU_HAS_LDAP_NETSCAPE_SSL
    st->have_certdb = 0;
#endif

    return st;
}

static void util_ldap_init_module(apr_pool_t *pool, server_rec *s)
{
    util_ldap_state_t *st = 
        (util_ldap_state_t *)ap_get_module_config(s->module_config, 
						  &ldap_module);

    apr_status_t result = util_ldap_cache_init(pool, st->cache_bytes);
    char buf[MAX_STRING_LEN];

    apr_strerror(result, buf, sizeof(buf));
    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                      "[%d] ldap cache init: %s", 
                      getpid(), buf);
}


command_rec util_ldap_cmds[] = {
    AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes, NULL, RSRC_CONF,
                  "Sets the size of the shared memory cache in bytes. "
                  "Zero means disable the shared memory cache. Defaults to 100KB."),

    AP_INIT_TAKE1("LDAPCacheEntries", util_ldap_set_cache_entries, NULL, RSRC_CONF,
                  "Sets the maximum number of entries that are possible in the LDAP "
                  "search cache. "
                  "Zero means no limit; -1 disables the cache. Defaults to 1024 entries."),

    AP_INIT_TAKE1("LDAPCacheTTL", util_ldap_set_cache_ttl, NULL, RSRC_CONF,
