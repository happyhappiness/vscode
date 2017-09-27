ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "proxy: ap_get_scoreboard_lb(%d) failed in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);