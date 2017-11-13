ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
            "AcceptMutex: %s (default: %s)",
            apr_proc_mutex_name(accept_mutex),
            apr_proc_mutex_defname());