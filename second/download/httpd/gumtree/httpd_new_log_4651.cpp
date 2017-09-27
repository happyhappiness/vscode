ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00931)
                 "initialized single connection worker in child %" APR_PID_T_FMT " for (%s)",
                 getpid(), worker->s->hostname);