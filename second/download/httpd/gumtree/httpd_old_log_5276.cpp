ap_log_error(APLOG_MARK,APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "master_main: WaitForMultipeObjects WAIT_FAILED -- doing server shutdown");