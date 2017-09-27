ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                             "apr_pollset_poll failed.  Attempting to "
                             "shutdown process gracefully");