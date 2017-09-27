
    if (!st->util_ldap_cache_lock) return;

    sts = apr_global_mutex_child_init(&st->util_ldap_cache_lock,
              apr_global_mutex_lockfile(st->util_ldap_cache_lock), p);
    if (sts != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s,
                     "Failed to initialise global mutex %s in child process",
                     ldap_cache_mutex_type);
    }
}

static const command_rec util_ldap_cmds[] = {
    AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes,
                  NULL, RSRC_CONF,
                  "Set the size of the shared memory cache (in bytes). Use "
                  "0 to disable the shared memory cache. (default: 100000)"),

    AP_INIT_TAKE1("LDAPSharedCacheFile", util_ldap_set_cache_file,
                  NULL, RSRC_CONF,
                  "Set the file name for the shared memory cache."),

    AP_INIT_TAKE1("LDAPCacheEntries", util_ldap_set_cache_entries,
                  NULL, RSRC_CONF,
                  "Set the maximum number of entries that are possible in the "
                  "LDAP search cache. Use 0 or -1 to disable the search cache " 
                  "(default: 1024)"),
                  
    AP_INIT_TAKE1("LDAPCacheTTL", util_ldap_set_cache_ttl,
                  NULL, RSRC_CONF,
                  "Set the maximum time (in seconds) that an item can be "
                  "cached in the LDAP search cache. Use 0 for no limit. "
                  "(default 600)"),

    AP_INIT_TAKE1("LDAPOpCacheEntries", util_ldap_set_opcache_entries,
                  NULL, RSRC_CONF,
                  "Set the maximum number of entries that are possible "
                  "in the LDAP compare cache. Use 0 or -1 to disable the compare cache " 
                  "(default: 1024)"),

    AP_INIT_TAKE1("LDAPOpCacheTTL", util_ldap_set_opcache_ttl,
                  NULL, RSRC_CONF,
                  "Set the maximum time (in seconds) that an item is cached "
                  "in the LDAP operation cache. Use 0 for no limit. "
