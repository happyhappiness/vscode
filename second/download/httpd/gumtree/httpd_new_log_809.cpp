ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
            "proxy: initialized worker %d in child %" APR_PID_T_FMT " for (%s) min=%d max=%d smax=%d",
             worker->id, getpid(), worker->hostname, worker->min,
             worker->hmax, worker->smax);