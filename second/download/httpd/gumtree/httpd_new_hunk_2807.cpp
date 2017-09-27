    if (err != NULL) {
        return err;
    }

    st->compare_cache_ttl = atol(ttl) * 1000000;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01301)
                 "ldap cache: Setting operation cache TTL to %ld microseconds.",
                 st->compare_cache_ttl);

    return NULL;
}

