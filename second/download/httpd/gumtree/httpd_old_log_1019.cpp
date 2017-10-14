ap_log_error(APLOG_MARK, APLOG_NOTICE, WSAGetLastError(), ap_server_conf,
                        "select() failed on listen socket");