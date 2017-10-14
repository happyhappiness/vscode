ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: server %s returned Transfer-Encoding"
                             " and Content-Length", backend->hostname);