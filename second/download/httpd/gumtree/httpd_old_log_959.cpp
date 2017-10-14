ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, status, pool,
                              "ap_listen_open: unable to make socket non-blocking");