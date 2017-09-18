ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_queue_info_wait failed. Attempting to "
                             " shutdown process gracefully.");