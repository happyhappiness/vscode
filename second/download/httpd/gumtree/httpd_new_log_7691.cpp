ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(02453)
                             "%s: error creating Unix domain socket for "
                             "target %s",
                             proxy_function,
                             worker->s->hostname);