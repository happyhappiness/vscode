ap_log_perror(APLOG_MARK, APLOG_ERR, rv, pool,
                      "DBD[%s] Error: %s", svr->name, errmsg );