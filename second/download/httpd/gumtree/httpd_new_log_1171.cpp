ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf,
                             "set_listeners_noninheritable: SetHandleInformation failed.");