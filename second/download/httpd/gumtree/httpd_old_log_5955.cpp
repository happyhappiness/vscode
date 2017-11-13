ap_log_error(APLOG_MARK, APLOG_CRIT, rs, s,
                     "Failed to reopen mutex %s in child",
                     exipc_mutex_type);