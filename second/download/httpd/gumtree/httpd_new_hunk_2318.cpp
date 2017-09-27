        return err;
    }

    st->cache_bytes = atol(bytes);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap cache: Setting shared memory cache size to "
                 "%" APR_SIZE_T_FMT " bytes.",
                 st->cache_bytes);

    return NULL;
}

static const char *util_ldap_set_cache_file(cmd_parms *cmd, void *dummy,
                                            const char *file)
