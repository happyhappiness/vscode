ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00933)
                         "%s: too soon to retry worker for (%s)",
                         proxy_function, worker->s->hostname);