ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01260)
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL again",
                  pid);