ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: read response failed from %pI (%s)",
                     conn->worker->cp->addr,
                     conn->worker->hostname);