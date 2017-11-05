ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf,
                     "OpenEvent on %s event", signal_name);