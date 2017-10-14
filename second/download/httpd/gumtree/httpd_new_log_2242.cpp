ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                 "winnt_accept: Too many failures grabbing a "
                                 "connection ctx.  Aborting.");