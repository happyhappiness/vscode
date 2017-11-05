ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02823)
                         "%s: connection established with Unix domain socket "
                         "%s (%s)",
                         proxy_function,
                         conn->uds_path,
                         worker->s->hostname);