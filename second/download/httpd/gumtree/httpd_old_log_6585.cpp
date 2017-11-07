ap_log_error(APLOG_MARK, APLOG_CRIT, status, s, APLOGNO(01758)
                     "error generating secret: %s",
                     apr_strerror(status, buf, sizeof(buf)));