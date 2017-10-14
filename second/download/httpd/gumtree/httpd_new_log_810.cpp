ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
             "proxy: initialized single connection worker %d in child %" APR_PID_T_FMT " for (%s)",
             worker->id, getpid(), worker->hostname);