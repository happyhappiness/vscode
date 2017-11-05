ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                     "caught exception in worker thread, initiating child shutdown pid=%d", getpid());