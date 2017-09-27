ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: send body failed to %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);