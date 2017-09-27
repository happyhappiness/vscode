            worker->cp->conn = conn;

            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00931)
                 "initialized single connection worker in child %" APR_PID_T_FMT " for (%s)",
                 getpid(), worker->s->hostname);
        }
    }
    if (rv == APR_SUCCESS) {
        worker->s->status |= (PROXY_WORKER_INITIALIZED);
        worker->local_status |= (PROXY_WORKER_INITIALIZED);
    }
    return rv;
