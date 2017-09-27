ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "
                             "shutdown process gracefully.");