    st->search_cache_size = atol(size);
    if (st->search_cache_size < 0) {
        st->search_cache_size = 0;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap cache: Setting search cache size to %ld entries.",
                 st->search_cache_size);

    return NULL;
}

static const char *util_ldap_set_opcache_ttl(cmd_parms *cmd, void *dummy,
                                             const char *ttl)
