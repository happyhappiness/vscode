ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, status, pool,
                              "unable to make listening socket non-blocking");