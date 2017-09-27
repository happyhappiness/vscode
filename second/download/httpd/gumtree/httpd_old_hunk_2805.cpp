    if (err != NULL) {
        return err;
    }

    st->search_cache_ttl = atol(ttl) * 1000000;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap cache: Setting cache TTL to %ld microseconds.",
                 st->search_cache_ttl);

    return NULL;
}

