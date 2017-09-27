ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: Can't connect to %s[%s]", svr->name, svr->params);