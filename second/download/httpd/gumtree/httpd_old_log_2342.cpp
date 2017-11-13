ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                                 (const server_rec *) ap_server_conf,
                                 "apr_pollset_poll: (listen)");