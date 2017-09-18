ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Parent: Unable to write duplicated socket %d to the child.", lr->sd );