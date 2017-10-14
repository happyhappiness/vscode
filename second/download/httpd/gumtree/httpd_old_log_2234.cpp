ap_log_error(APLOG_MARK, APLOG_INFO, apr_get_netos_error(), ap_server_conf,
                         "select failed with error %d", apr_get_netos_error());