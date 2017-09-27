ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00632)
                     "failed to prepare SQL statements: %s",
                     (errmsg ? errmsg : "[???]"));