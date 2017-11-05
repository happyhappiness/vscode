ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00952)
                         "%s: error creating fam %d socket for target %s",
                         proxy_function,
                         backend_addr->family,
                         worker->s->hostname);