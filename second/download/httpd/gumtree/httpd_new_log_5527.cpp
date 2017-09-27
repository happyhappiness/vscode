ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s,
                 "mpm child %" APR_PID_T_FMT " (gen %d/slot %d) %s",
                 pid, gen, slot, status_msg);