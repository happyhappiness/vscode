ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00957)
                         "%s: attempt to connect to %pI (%s) failed",
                         proxy_function,
                         backend_addr,
                         worker->s->hostname);