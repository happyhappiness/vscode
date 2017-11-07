ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02454)
                             "%s: attempt to connect to Unix domain socket "
                             "%s (%s) failed",
                             proxy_function,
                             conn->uds_path,
                             worker->s->hostname);