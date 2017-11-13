ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                      "DBD: driver for %s not available", svr->name);