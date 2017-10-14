ap_log_error(APLOG_MARK, APLOG_WARNING,
                                     apr_get_os_error(), ap_server_conf,
                             "winnt_accept: Asynchronous AcceptEx failed.");