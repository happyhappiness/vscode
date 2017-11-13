ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap cache: Setting operation cache TTL to %ld microseconds.",
                 getpid(), st->compare_cache_ttl);