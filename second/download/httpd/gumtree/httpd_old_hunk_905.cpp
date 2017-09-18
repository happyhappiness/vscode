    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                      "[%d] ldap cache init: %s", 
                      getpid(), buf);
}


command_rec util_ldap_cmds[] = {
    AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes, NULL, RSRC_CONF,
                  "Sets the size of the shared memory cache in bytes. "
                  "Zero means disable the shared memory cache. Defaults to 100KB."),

    AP_INIT_TAKE1("LDAPCacheEntries", util_ldap_set_cache_entries, NULL, RSRC_CONF,
