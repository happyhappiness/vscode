ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT,
                     APR_EBADPATH, NULL, "Invalid -E error log file %s",
                     fname);