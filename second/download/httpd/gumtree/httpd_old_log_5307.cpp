ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Parent: Cannot create restart event %s", signal_restart_name);