ap_log_error(APLOG_MARK, loglevel, rv, s,
                                 "proxy: %s: attempt to connect to %s:%d "
                                 "via http CONNECT through %pI (%s) failed",
                                 proxy_function,
                                 forward->target_host, forward->target_port,
                                 backend_addr, worker->hostname);