ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00930)
                "initialized pool in child %" APR_PID_T_FMT " for (%s) min=%d max=%d smax=%d",
                 getpid(), worker->s->hostname, worker->s->min,
                 worker->s->hmax, worker->s->smax);