ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized plain memory in child %" APR_PID_T_FMT " for worker %s",
              getpid(), worker->name);