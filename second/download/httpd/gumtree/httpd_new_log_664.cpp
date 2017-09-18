ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH, 
                     NULL, "Invalid PID file path %s, ignoring.", filename);