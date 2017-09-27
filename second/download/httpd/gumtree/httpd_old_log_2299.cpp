ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), ap_server_conf,
                             "Too many errors in select loop. Child process exiting.");