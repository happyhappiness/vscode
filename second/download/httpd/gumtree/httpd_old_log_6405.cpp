ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                             "apr_thread_create: unable to create worker thread");