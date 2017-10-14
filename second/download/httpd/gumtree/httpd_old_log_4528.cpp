ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                      "proxy: grabbed scoreboard slot %d in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);