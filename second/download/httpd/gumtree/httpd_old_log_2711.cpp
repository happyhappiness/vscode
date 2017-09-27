ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                      "DBD: driver for %s is invalid or corrupted", svr->name);