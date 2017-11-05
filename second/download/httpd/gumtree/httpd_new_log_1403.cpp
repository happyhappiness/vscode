ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
                      "DBD: failed to initialise prepared SQL statements: %s",
                      (errmsg ? errmsg : "[???]"));