ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01259)
                  "CGI process %" APR_PID_T_FMT " didn't exit, sending SIGKILL",
                  pid);