ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH,
                     NULL, APLOGNO(00101) "Invalid PID file path %s, ignoring.", filename);