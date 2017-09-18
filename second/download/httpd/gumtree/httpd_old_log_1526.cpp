ap_log_error(APLOG_MARK, APLOG_NOTICE, apr_get_netos_error(), ap_server_conf,
                        "select() failed on listen socket");