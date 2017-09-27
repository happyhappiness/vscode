    if (err != NULL) {
        return err;
    }

    st->cache_bytes = atol(bytes);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01297)
                 "ldap cache: Setting shared memory cache size to "
                 "%" APR_SIZE_T_FMT " bytes.",
                 st->cache_bytes);

    return NULL;
}
