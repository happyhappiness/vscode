ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: CONNECT: sending the CONNECT request for %s:%d "
                 "to the remote proxy %pI (%s)",
                 forward->target_host, forward->target_port,
                 backend->addr, backend->hostname);