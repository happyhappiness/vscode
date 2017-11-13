ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(02643)
                         "Child: Failed to open handle to parent process %ld; "
                         "will not react to abrupt parent termination", parent_pid);