ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                      "DBD: can't find driver for %s", svr->name);