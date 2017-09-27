        return err;
    }

    st->search_cache_ttl = atol(ttl) * 1000000;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap cache: Setting cache TTL to %ld microseconds.",
                 getpid(), st->search_cache_ttl);

    return NULL;
}

static const char *util_ldap_set_cache_entries(cmd_parms *cmd, void *dummy,
                                               const char *size)
