ap_log_error(APLOG_MARK,APLOG_WARNING, GetLastError(), ap_server_conf,
                                     "winnt_accept: Asynchronous AcceptEx failed.");