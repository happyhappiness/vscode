ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                 "DBD [%s] Error: %s", svr->cfg->name, errmsg);