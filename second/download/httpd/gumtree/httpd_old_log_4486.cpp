ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: " PROXY_FUNCTION ": failed to make connection "
                     "to backend: %s:%u", backend->hostname, backend->port);