ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap cache: Setting search cache size to %ld entries.",
                 st->search_cache_size);