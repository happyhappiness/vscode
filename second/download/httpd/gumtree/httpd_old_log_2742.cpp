ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                 "proxy: got bad response (%d) from %pI (%s)",
                 result,
                 conn->worker->cp->addr,
                 conn->worker->hostname);