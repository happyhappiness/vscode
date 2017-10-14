ap_log_error(APLOG_MARK, APLOG_ERR,
                     0, ap_server_conf, APLOGNO(00046)
                     "child process %" APR_PID_T_FMT
                     " still did not exit, "
                     "sending a SIGKILL",
                     pid);