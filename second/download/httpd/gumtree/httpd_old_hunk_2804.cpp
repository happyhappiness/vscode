        st->cache_file = ap_server_root_relative(st->pool, file);
    }
    else {
        st->cache_file = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "LDAP cache: Setting shared memory cache file to %s bytes.",
                 st->cache_file);

    return NULL;
}

