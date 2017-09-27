ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                "[%" APR_PID_T_FMT " - %s] "
                "child second stage post config hook",
                getpid(), ppid);