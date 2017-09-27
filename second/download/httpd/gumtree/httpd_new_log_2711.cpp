ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
                         "DBD: driver for %s is invalid or corrupted",
                         cfg->name);