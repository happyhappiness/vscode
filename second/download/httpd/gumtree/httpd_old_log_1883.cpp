ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap cache: Setting search cache size to %ld entries.",
                 getpid(), st->search_cache_size);