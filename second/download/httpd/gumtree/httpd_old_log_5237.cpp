ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf,
                     "SetEvent on %s event", signal_name);