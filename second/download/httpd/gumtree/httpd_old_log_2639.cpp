ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                      "DBD: Can't connect to %s", svr->name);