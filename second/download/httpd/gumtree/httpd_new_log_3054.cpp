ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s,
                     "Failed to initialise global mutex %s in child process",
                     ldap_cache_mutex_type);