ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: got response from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);